import math
import random
import time


def play(gameState, memo={}):
    # =====================================================================
    #  ROCK-PAPER-SCISSORS RACE BOT  --  negamax / alpha-beta search engine
    #
    #  Features (each one has a switch below):
    #    - iterative deepening with a CPU-time budget (per move AND per game)
    #    - negamax + alpha-beta, principal variation search (PVS)
    #    - aspiration windows
    #    - transposition table (Zobrist hashing, kept between moves in `memo`)
    #    - quiescence search (captures + "must stop an immediate goal" replies)
    #    - move ordering: TT move > safe captures > unsafe captures >
    #                     killers > history heuristic > forward moves
    #    - selectivity: late move reductions, late move pruning, futility
    #      pruning, reverse futility pruning, pruning of hanging quiet moves
    #    - extensions: "opponent threatens to reach the goal", recapture
    #    - repetition avoidance (positions already seen in this game)
    #
    #  HOW TO TUNE: only touch the sections "1. TUNABLE PARAMETERS" below.
    #  Everything is plain numbers / True-False switches.
    # =====================================================================

    # =====================================================================
    # 1. TUNABLE PARAMETERS
    # =====================================================================
    DEBUG = False  # True -> print depth / score / nodes after every move

    # ---------------- time management (CPU seconds) ----------------
    TOTAL_CPU_BUDGET = 160.0  # whole-game budget we allow ourselves (hard limit is 180)
    MAX_MOVE_TIME = (
        0.80  # never think longer than this on a normal move (hard limit 1.0)
    )
    MIN_MOVE_TIME = 0.05  # never think less than this (unless the move is forced)
    FIRST_MOVE_TIME = 4.0  # first move of a game (hard limit 10, includes start-up)
    BUDGET_SPREAD = 2.0  # move time = remaining_budget / moves_left * BUDGET_SPREAD
    #   higher = think longer early, less when the game drags on
    SOFT_TIME_FRACTION = (
        0.60  # do not START a new depth after this share of the move time
    )
    NEXT_ITER_FACTOR = (
        3.0  # ...or if (elapsed + last_iteration_time * this) > move time
    )
    TIME_CHECK_EVERY = 64  # check the clock every N nodes (must be a power of two)
    FALLBACK_AVG_MOVE_TIME = (
        0.4  # if memory was wiped mid-game: assume this much CPU per past move
    )

    # ---------------- search: general ----------------
    MAX_DEPTH = 40  # iterative deepening never goes deeper than this
    MAX_PLY = 64  # hard cap on recursion depth (extensions included)
    USE_TT = True  # transposition table
    TT_MAX_ENTRIES = 300000  # table is cleared when it grows beyond this (memory!)
    USE_PVS = True  # null-window search for every move except the first
    USE_ASPIRATION = True  # search root with a narrow window around last score
    ASP_START_DEPTH = 4  # first depth that uses aspiration windows
    ASP_DELTA = 40  # initial half-width of the window (eval units, 100 = 1 piece)
    ASP_WIDEN = 3  # window grows by this factor after each failure

    # ---------------- quiescence search ----------------
    USE_QSEARCH = True  # False -> leaf nodes just call the evaluation
    QS_MAX_DEPTH = 10  # max extra plies of capture-only search
    QS_THREAT_DEPTH = 4  # max extra plies when we must stop an immediate goal-run
    USE_QS_DELTA = True  # skip qsearch if even winning a piece cannot reach alpha
    QS_DELTA_MARGIN = 200

    # ---------------- extensions ----------------
    THREAT_EXTENSION = (
        1  # plies added when the opponent can reach its goal next move (0 = off)
    )
    THREAT_EXT_PLY_MARGIN = 6  # extensions only while ply < iteration_depth + this
    RECAPTURE_EXTENSION = (
        0  # plies added when we recapture on the square just captured (0 = off)
    )

    # ---------------- selectivity (forward pruning / reductions) ----------------
    USE_LMR = True  # late move reductions
    LMR_MIN_DEPTH = 3  # only reduce when remaining depth >= this
    LMR_MIN_INDEX = 3  # only reduce quiet moves searched after this many moves
    LMR_REDUCTION = 1  # plies removed
    LMR_DEEP_DEPTH = 5  # extra reduction when depth >= this ...
    LMR_DEEP_INDEX = 8  # ... and the move index >= this

    USE_FUTILITY = True  # skip quiet moves when static eval + margin <= alpha
    FUTILITY_MARGIN = (
        0,
        130,
        260,
    )  # indexed by remaining depth (0,1,2); deeper = no futility

    USE_LMP = True  # late move pruning: at low depth only try the first N quiet moves
    LMP_LIMITS = (0, 10, 16, 24)  # indexed by remaining depth (0..3); deeper = no LMP

    USE_RFP = True  # reverse futility: static eval far above beta -> return at once
    RFP_MARGIN = 150  # margin per remaining ply
    RFP_MAX_DEPTH = 2

    PRUNE_UNSAFE_QUIET = (
        True  # skip quiet moves onto squares an enemy can capture (if unprotected)
    )
    UNSAFE_PRUNE_DEPTH = 2  # ... only when remaining depth <= this
    PRUNE_SAFE_DIST = (
        3  # never prune a move that ends within this many steps of the goal
    )

    # ---------------- move ordering ----------------
    ORDER_ADV_W = 30  # quiet-move ordering bonus per step closer to the goal
    HIST_BONUS = 32  # history heuristic: += depth^2 * this on a quiet cutoff
    HIST_CAP = 700000  # history values never exceed this
    UNSAFE_QUIET_PEN = 1200000  # quiet moves into capturable squares go to the back

    # ---------------- evaluation (100 = value of one piece) ----------------
    MATERIAL = 100  # value of one piece
    # ADVANCE_W = 4                 # per piece: this * (8 - steps_to_goal)
    # bonus for our most advanced piece, indexed by its distance to the goal (0..9)
    LEAD_BONUS = (0, 120, 70, 40, 22, 12, 6, 2, 0, 0)
    TEMPO_BONUS = 8  # bonus for the side to move
    # TYPE_PAIR_W = 6               # per (my piece beats his piece) pair minus (his beats mine) pairs
    INVULN_BONUS = 30  # per piece whose predator type is extinct on the other side
    REPEAT_SCORE = (
        -15
    )  # value (for US) of reaching an already-seen position; <0 avoids repeats
    COUNT_W = 0.0  # recommended 0 for now (0.03 tested worse)
    COUNTER_W = 0.08
    PROGRESS_W = 0.04
    DISCONNECT_W = 0.05
    DISCONNECT_FREE = 1.5
    MIN_PIECE_FACTOR = 0.3

    # =====================================================================
    # 2. CONSTANTS (don't edit)
    # =====================================================================
    INF = 10**9
    MATE = 100000
    MATE_THRESH = MATE - 500
    EXACT = 0
    LOWER = 1
    UPPER = 2
    EMPTY = -1
    WALL = -2
    OFFS = (10, 11, 12, 1, -10, -11, -12, -1)  # direction codes 1,2,3,4,5,6,7,8
    OFF_TO_DIR = {10: 1, 11: 2, 12: 3, 1: 4, -10: 5, -11: 6, -12: 7, -1: 8}
    TMAP = {"R": 0, "P": 1, "S": 2}
    PRED_BIT = (1 << 1, 1 << 2, 1 << 0)  # bit of the type that beats type t
    TCHK = TIME_CHECK_EVERY - 1
    OFFS_SC = 1 << 22  # makes move-order scores positive
    SC_TT = 5000000
    SC_CAP_SAFE = 3000000
    SC_CAP_UNSAFE = 2000000
    SC_KILLER1 = 1500000
    SC_KILLER2 = 1400000
    STATIC_EVAL_DEPTH = max(len(FUTILITY_MARGIN) - 1, RFP_MAX_DEPTH)
    LMP_MAX_DEPTH = len(LMP_LIMITS) - 1

    # =====================================================================
    # 3. EVALUATION FUNCTION  (self-contained: edit this block to change how
    #    positions are judged; the search only calls evaluate(...))
    #
    #    Position format (the search keeps these arrays up to date):
    #      psq[k]  square of piece k (y*11 + x), or -1 if captured
    #      TYPE[k] 0 = R, 1 = P, 2 = S
    #      k = 0..8 are OUR pieces, k = 9..17 are the ENEMY pieces
    #      cnt[0], cnt[1] = number of pieces still alive for us / the enemy
    #    Returns a score from the point of view of `side` (0 = us, 1 = enemy),
    #    the side to move. Positive = good for `side`. 100 = one piece.
    # =====================================================================
    # distance (king moves) of every square to the goal of each side
    DST = ([99] * 121, [99] * 121)
    for _y in range(1, 10):
        for _x in range(1, 10):
            DST[0][_y * 11 + _x] = max(9 - _x, 9 - _y)  # side 0 (us) runs to (9,9)
            DST[1][_y * 11 + _x] = max(_x - 1, _y - 1)  # side 1 (enemy) runs to (1,1)
        XS = [sq % 11 for sq in range(121)]
    YS = [sq // 11 for sq in range(121)]

    def evaluate(side, psq, TYPE, cnt):
        # pass 1: type counts, group centre, most advanced piece of each side
        c0 = [0, 0, 0]
        c1 = [0, 0, 0]
        sx0 = sy0 = sx1 = sy1 = 0
        m0 = 9
        m1 = 9
        d0 = DST[0]
        d1 = DST[1]
        for k in range(0, 9):
            sq = psq[k]
            if sq >= 0:
                c0[TYPE[k]] += 1
                sx0 += XS[sq]
                sy0 += YS[sq]
                if d0[sq] < m0:
                    m0 = d0[sq]
        for k in range(9, 18):
            sq = psq[k]
            if sq >= 0:
                c1[TYPE[k]] += 1
                sx1 += XS[sq]
                sy1 += YS[sq]
                if d1[sq] < m1:
                    m1 = d1[sq]
        n0 = cnt[0] if cnt[0] > 0 else 1
        n1 = cnt[1] if cnt[1] > 0 else 1
        cx0 = sx0 / n0
        cy0 = sy0 / n0
        cx1 = sx1 / n1
        cy1 = sy1 / n1

        # pass 2: value every piece = 1 + linear factors
        v0 = 0.0
        for k in range(0, 9):
            sq = psq[k]
            if sq >= 0:
                t = TYPE[k]
                far = max(abs(XS[sq] - cx0), abs(YS[sq] - cy0)) - DISCONNECT_FREE
                if far < 0:
                    far = 0
                f = (
                    1.0
                    + COUNT_W * c0[t]
                    + COUNTER_W * c1[(t + 2) % 3]
                    + PROGRESS_W * (8 - d0[sq])
                    - DISCONNECT_W * far
                )
                v0 += f if f > MIN_PIECE_FACTOR else MIN_PIECE_FACTOR
        v1 = 0.0
        for k in range(9, 18):
            sq = psq[k]
            if sq >= 0:
                t = TYPE[k]
                far = max(abs(XS[sq] - cx1), abs(YS[sq] - cy1)) - DISCONNECT_FREE
                if far < 0:
                    far = 0
                f = (
                    1.0
                    + COUNT_W * c1[t]
                    + COUNTER_W * c0[(t + 2) % 3]
                    + PROGRESS_W * (8 - d1[sq])
                    - DISCONNECT_W * far
                )
                v1 += f if f > MIN_PIECE_FACTOR else MIN_PIECE_FACTOR

        s = int(MATERIAL * (v0 - v1)) + LEAD_BONUS[m0] - LEAD_BONUS[m1]
        for t in (0, 1, 2):
            if c0[t] and not c1[(t + 1) % 3]:
                s += INVULN_BONUS * c0[t]
            if c1[t] and not c0[(t + 1) % 3]:
                s -= INVULN_BONUS * c1[t]
        return (s if side == 0 else -s) + TEMPO_BONUS

    t_enter = time.process_time()

    # ---------------------------------------------------------------------
    # simple greedy fallback (used only if the engine crashes)
    # ---------------------------------------------------------------------
    def fallback():
        STEP = {
            1: (-1, 1),
            2: (0, 1),
            3: (1, 1),
            4: (1, 0),
            5: (1, -1),
            6: (0, -1),
            7: (-1, -1),
            8: (-1, 0),
        }
        BEATS = {"R": "S", "S": "P", "P": "R"}
        mine = {(p.x, p.y) for p in gameState.ally}
        enemy = {(p.x, p.y): p.Type for p in gameState.opponent}
        moves = []
        for p in gameState.ally:
            for d, (dx, dy) in STEP.items():
                nx, ny = p.x + dx, p.y + dy
                if not (1 <= nx <= 9 and 1 <= ny <= 9) or (nx, ny) in mine:
                    continue
                t = enemy.get((nx, ny))
                if t is None or BEATS[p.Type] == t:
                    moves.append((max(9 - nx, 9 - ny), p.pid, d))
        if not moves:
            return (0, 0)
        random.shuffle(moves)
        best = min(moves, key=lambda mv: mv[0])
        return (best[1], best[2])

    # ---------------------------------------------------------------------
    # the engine
    # ---------------------------------------------------------------------
    def search_move():
        turn = gameState.currentTurn

        # ---- persistent memory (survives between moves, wiped if we time out) ----
        fresh = "tt" not in memo
        if fresh:
            memo["tt"] = {}
            memo["hist"] = {}
            memo["seen"] = set()
            memo["ZKT"] = [
                [random.getrandbits(60) for _ in range(128)] for _ in range(6)
            ]
            memo["ZS"] = random.getrandbits(60)
            memo["used"] = 0.0 if turn < 2 else (turn // 2) * FALLBACK_AVG_MOVE_TIME
        tt = memo["tt"]
        hist = memo["hist"]
        seen = memo["seen"]
        ZKT = memo["ZKT"]
        ZS = memo["ZS"]
        if len(tt) > TT_MAX_ENTRIES:
            tt.clear()
        for kk in list(hist.keys()):  # age the history heuristic
            v = hist[kk] >> 1
            if v:
                hist[kk] = v
            else:
                del hist[kk]

        # ---- time budget for this move ----
        if turn < 2 and fresh:
            alloc = FIRST_MOVE_TIME
        else:
            moves_left = max(1, (gameState.maxTurn - turn + 1) // 2)
            remaining = TOTAL_CPU_BUDGET - memo["used"]
            alloc = remaining / moves_left * BUDGET_SPREAD
            alloc = max(MIN_MOVE_TIME, min(MAX_MOVE_TIME, alloc))
        deadline = t_enter + alloc

        # ---- board: 11x11 padded array, square = y*11 + x ----
        #  board[sq] = piece id (0..8 mine, 9..17 enemy), EMPTY or WALL
        board = [WALL] * 121
        for y in range(1, 10):
            for x in range(1, 10):
                board[y * 11 + x] = EMPTY
        TYPE = [0] * 18
        psq = [-1] * 18
        PIDS = [0] * 18
        cnt = [0, 0]
        for i, p in enumerate(gameState.ally):
            sq = p.y * 11 + p.x
            TYPE[i] = TMAP[p.Type]
            psq[i] = sq
            PIDS[i] = p.pid
            board[sq] = i
            cnt[0] += 1
        for i, p in enumerate(gameState.opponent):
            sq = p.y * 11 + p.x
            TYPE[9 + i] = TMAP[p.Type]
            psq[9 + i] = sq
            PIDS[9 + i] = p.pid
            board[sq] = 9 + i
            cnt[1] += 1
        SIDE = [0] * 9 + [1] * 9
        PR = (range(0, 9), range(9, 18))
        ZK = [ZKT[SIDE[k] * 3 + TYPE[k]] for k in range(18)]

        GOAL = (9 * 11 + 9, 1 * 11 + 1)
        NB = (
            (GOAL[0] - 1, GOAL[0] - 11, GOAL[0] - 12),
            (GOAL[1] + 1, GOAL[1] + 11, GOAL[1] + 12),
        )

        killers = [[0, 0] for _ in range(MAX_PLY + 4)]
        path = [0] * (MAX_PLY + 4)
        nodes = [0]
        stop = [False]
        ext_limit = [0]
        scores = {}

        # -----------------------------------------------------------------
        # helpers
        # -----------------------------------------------------------------
        def win_move(side):
            # a legal move that puts a piece of `side` on its goal, or 0
            g = GOAL[side]
            gv = board[g]
            for n in NB[side]:
                v = board[n]
                if v >= 0 and SIDE[v] == side:
                    if gv == EMPTY or (
                        SIDE[gv] != side and (TYPE[v] - TYPE[gv]) % 3 == 1
                    ):
                        return (n << 7) | g
            return 0

        def attacked(sq, by_side, t):
            # can a piece of `by_side` capture a piece of type t standing on sq?
            pt = (t + 1) % 3
            for off in OFFS:
                v = board[sq + off]
                if v >= 0 and SIDE[v] == by_side and TYPE[v] == pt:
                    return True
            return False

        def protected(sq, side, t):
            # does `side` have a neighbour of sq able to recapture the attacker of a type-t piece?
            q = (t + 2) % 3
            for off in OFFS:
                v = board[sq + off]
                if v >= 0 and SIDE[v] == side and TYPE[v] == q:
                    return True
            return False

        def gen_main(side, ply, tt_move):
            # all non-suicidal moves for `side`, best-first, as packed ints (score<<14 | from<<7 | to)
            opp = 1 - side
            eatt = [0] * 121  # eatt[sq] = bit mask of enemy piece types adjacent to sq
            for k in PR[opp]:
                sq = psq[k]
                if sq >= 0:
                    bit = 1 << TYPE[k]
                    for off in OFFS:
                        eatt[sq + off] |= bit
            out = []
            kl = killers[ply]
            k0 = kl[0]
            k1 = kl[1]
            dst = DST[side]
            hbase = side << 14
            for k in PR[side]:
                frm = psq[k]
                if frm < 0:
                    continue
                t = TYPE[k]
                pb = PRED_BIT[t]
                fb = frm << 7
                for off in OFFS:
                    to = frm + off
                    v = board[to]
                    if v == EMPTY:
                        m = fb | to
                        if m == tt_move:
                            sc = SC_TT
                        elif m == k0:
                            sc = SC_KILLER1
                        elif m == k1:
                            sc = SC_KILLER2
                        else:
                            sc = (
                                1000
                                + ORDER_ADV_W * (dst[frm] - dst[to])
                                + hist.get(hbase | m, 0)
                            )
                            if eatt[to] & pb:
                                sc -= UNSAFE_QUIET_PEN
                        out.append(((sc + OFFS_SC) << 14) | m)
                    elif v >= 0 and SIDE[v] == opp and (t - TYPE[v]) % 3 == 1:
                        m = fb | to
                        if m == tt_move:
                            sc = SC_TT
                        elif eatt[to] & pb:
                            sc = SC_CAP_UNSAFE
                        else:
                            sc = SC_CAP_SAFE
                        out.append(((sc + OFFS_SC) << 14) | m)
            out.sort(reverse=True)
            return out, eatt

        def gen_q(side, caps_only):
            # captures (and, if not caps_only, quiet moves) for the quiescence search
            opp = 1 - side
            out = []
            for k in PR[side]:
                frm = psq[k]
                if frm < 0:
                    continue
                t = TYPE[k]
                fb = frm << 7
                for off in OFFS:
                    to = frm + off
                    v = board[to]
                    if v == EMPTY:
                        if not caps_only:
                            out.append((OFFS_SC << 14) | fb | to)
                    elif v >= 0 and SIDE[v] == opp and (t - TYPE[v]) % 3 == 1:
                        sc = SC_CAP_UNSAFE if attacked(to, opp, t) else SC_CAP_SAFE
                        out.append(((sc + OFFS_SC) << 14) | fb | to)
            out.sort(reverse=True)
            return out

        # -----------------------------------------------------------------
        # quiescence search
        # -----------------------------------------------------------------
        def qsearch(alpha, beta, side, ply, qd):
            nodes[0] += 1
            if not (nodes[0] & TCHK):
                if time.process_time() >= deadline:
                    stop[0] = True
            if stop[0]:
                return 0
            opp = 1 - side
            if cnt[side] == 0:
                return -(MATE - ply)
            if win_move(side):
                return MATE - ply - 1
            if ply >= MAX_PLY - 2:
                return evaluate(side, psq, TYPE, cnt)
            if win_move(opp):
                # we MUST stop an immediate goal-run: look at every move, no stand-pat
                if qd >= QS_THREAT_DEPTH:
                    return evaluate(side, psq, TYPE, cnt)
                best = -INF
                moves = gen_q(side, False)
                if not moves:
                    return -(MATE - ply - 2)
            else:
                stand = evaluate(side, psq, TYPE, cnt)
                if stand >= beta or qd >= QS_MAX_DEPTH:
                    return stand
                if USE_QS_DELTA and stand + MATERIAL + QS_DELTA_MARGIN <= alpha:
                    return stand
                if stand > alpha:
                    alpha = stand
                best = stand
                moves = gen_q(side, True)
            for key in moves:
                m = key & 16383
                frm = m >> 7
                to = m & 127
                cap = board[to]
                k = board[frm]
                board[frm] = EMPTY
                board[to] = k
                psq[k] = to
                if cap >= 0:
                    psq[cap] = -1
                    cnt[opp] -= 1
                score = -qsearch(-beta, -alpha, opp, ply + 1, qd + 1)
                board[to] = cap
                board[frm] = k
                psq[k] = frm
                if cap >= 0:
                    psq[cap] = to
                    cnt[opp] += 1
                if stop[0]:
                    return 0
                if score > best:
                    best = score
                    if score > alpha:
                        alpha = score
                        if alpha >= beta:
                            break
            return best

        # -----------------------------------------------------------------
        # main negamax (alpha-beta, PVS, TT, LMR, pruning, extensions)
        #   side: 0 = us, 1 = enemy;  lc: square of the last capture (or 0)
        # -----------------------------------------------------------------
        def negamax(depth, alpha, beta, side, ply, h, lc):
            nodes[0] += 1
            if not (nodes[0] & TCHK):
                if time.process_time() >= deadline:
                    stop[0] = True
            if stop[0]:
                return 0
            opp = 1 - side
            if cnt[side] == 0:
                return -(MATE - ply)
            if win_move(side):
                return MATE - ply - 1
            if ply >= MAX_PLY - 2:
                return evaluate(side, psq, TYPE, cnt)
            if h in seen or (ply >= 4 and path[ply - 4] == h):
                return REPEAT_SCORE if side == 0 else -REPEAT_SCORE
            path[ply] = h

            # ---- extension: the opponent threatens to reach its goal ----
            threat = win_move(opp) != 0
            if threat and THREAT_EXTENSION and ply < ext_limit[0]:
                depth += THREAT_EXTENSION
            if depth <= 0:
                if USE_QSEARCH:
                    return qsearch(alpha, beta, side, ply, 0)
                return evaluate(side, psq, TYPE, cnt)

            # ---- transposition table ----
            alpha0 = alpha
            tt_move = 0
            if USE_TT:
                e = tt.get(h)
                if e is not None:
                    tt_move = e[3]
                    if e[0] >= depth:
                        sc = e[2]
                        if sc > MATE_THRESH:
                            sc -= ply
                        elif sc < -MATE_THRESH:
                            sc += ply
                        fl = e[1]
                        if fl == EXACT:
                            return sc
                        if fl == LOWER and sc >= beta:
                            return sc
                        if fl == UPPER and sc <= alpha:
                            return sc

            # ---- static eval for the selectivity rules ----
            static = None
            if (not threat) and depth <= STATIC_EVAL_DEPTH:
                static = evaluate(side, psq, TYPE, cnt)
                if (
                    USE_RFP
                    and depth <= RFP_MAX_DEPTH
                    and beta < MATE_THRESH
                    and static - RFP_MARGIN * depth >= beta
                ):
                    return static - RFP_MARGIN * depth

            moves, eatt = gen_main(side, ply, tt_move)
            if not moves:
                # nothing legal: we pass
                return -negamax(depth - 1, -beta, -alpha, opp, ply + 1, h ^ ZS, 0)

            dst = DST[side]
            best = -INF
            best_m = 0
            searched = 0
            no_mate = (-MATE_THRESH < alpha) and (beta < MATE_THRESH)
            for key in moves:
                m = key & 16383
                frm = m >> 7
                to = m & 127
                cap = board[to]
                k = board[frm]
                quiet = cap < 0

                # ---- forward pruning of quiet moves ----
                if (
                    quiet
                    and searched > 0
                    and (not threat)
                    and no_mate
                    and dst[to] > PRUNE_SAFE_DIST
                ):
                    if (
                        USE_LMP
                        and depth <= LMP_MAX_DEPTH
                        and searched >= LMP_LIMITS[depth]
                    ):
                        continue
                    if (
                        USE_FUTILITY
                        and static is not None
                        and depth < len(FUTILITY_MARGIN)
                        and static + FUTILITY_MARGIN[depth] <= alpha
                    ):
                        continue
                    if (
                        PRUNE_UNSAFE_QUIET
                        and depth <= UNSAFE_PRUNE_DEPTH
                        and (eatt[to] & PRED_BIT[TYPE[k]])
                        and not protected(to, side, TYPE[k])
                    ):
                        continue

                # ---- make move ----
                nh = h ^ ZK[k][frm] ^ ZK[k][to] ^ ZS
                board[frm] = EMPTY
                board[to] = k
                psq[k] = to
                nd = depth - 1
                nlc = 0
                if cap >= 0:
                    nh ^= ZK[cap][to]
                    psq[cap] = -1
                    cnt[opp] -= 1
                    nlc = to
                    if RECAPTURE_EXTENSION and to == lc:
                        nd += RECAPTURE_EXTENSION

                # ---- search ----
                if searched == 0:
                    score = -negamax(nd, -beta, -alpha, opp, ply + 1, nh, nlc)
                else:
                    red = 0
                    if (
                        USE_LMR
                        and quiet
                        and (not threat)
                        and depth >= LMR_MIN_DEPTH
                        and searched >= LMR_MIN_INDEX
                    ):
                        red = LMR_REDUCTION
                        if depth >= LMR_DEEP_DEPTH and searched >= LMR_DEEP_INDEX:
                            red += 1
                        if red > nd - 1:
                            red = nd - 1
                        if red < 0:
                            red = 0
                    if USE_PVS:
                        score = -negamax(
                            nd - red, -alpha - 1, -alpha, opp, ply + 1, nh, nlc
                        )
                        if score > alpha and red > 0:
                            score = -negamax(
                                nd, -alpha - 1, -alpha, opp, ply + 1, nh, nlc
                            )
                        if score > alpha and score < beta and beta - alpha > 1:
                            score = -negamax(nd, -beta, -alpha, opp, ply + 1, nh, nlc)
                    else:
                        score = -negamax(nd - red, -beta, -alpha, opp, ply + 1, nh, nlc)
                        if red > 0 and score > alpha:
                            score = -negamax(nd, -beta, -alpha, opp, ply + 1, nh, nlc)

                # ---- unmake move ----
                board[to] = cap
                board[frm] = k
                psq[k] = frm
                if cap >= 0:
                    psq[cap] = to
                    cnt[opp] += 1
                if stop[0]:
                    return 0
                searched += 1

                if score > best:
                    best = score
                    best_m = m
                    if score > alpha:
                        alpha = score
                        if alpha >= beta:
                            if quiet:
                                kl = killers[ply]
                                if kl[0] != m:
                                    kl[1] = kl[0]
                                    kl[0] = m
                                hk = (side << 14) | m
                                hv = hist.get(hk, 0) + depth * depth * HIST_BONUS
                                hist[hk] = hv if hv < HIST_CAP else HIST_CAP
                            break

            if USE_TT:
                if best <= alpha0:
                    fl = UPPER
                elif best >= beta:
                    fl = LOWER
                else:
                    fl = EXACT
                sc = best
                if sc > MATE_THRESH:
                    sc += ply
                elif sc < -MATE_THRESH:
                    sc -= ply
                old = tt.get(h)
                if old is None or old[0] <= depth:
                    tt[h] = (depth, fl, sc, best_m)
            return best

        # -----------------------------------------------------------------
        # root
        # -----------------------------------------------------------------
        h0 = 0
        for k in range(18):
            if psq[k] >= 0:
                h0 ^= ZK[k][psq[k]]
        seen.add(h0)

        def finish(m):
            frm = m >> 7
            to = m & 127
            k = board[frm]
            nh = h0 ^ ZK[k][frm] ^ ZK[k][to] ^ ZS
            cp = board[to]
            if cp >= 0:
                nh ^= ZK[cp][to]
            seen.add(nh)
            return (PIDS[k], OFF_TO_DIR[to - frm])

        wm = win_move(0)
        if wm:
            return finish(wm)
        tt_move0 = 0
        e0 = tt.get(h0)
        if e0 is not None:
            tt_move0 = e0[3]
        keys, eatt0 = gen_main(0, 0, tt_move0)
        root_moves = [kk & 16383 for kk in keys]
        if not root_moves:
            return (0, 0)  # no legal move: pass
        if len(root_moves) == 1:
            return finish(root_moves[0])

        def root_iter(depth, alpha, beta):
            a = alpha
            best_s = -INF
            best_m = 0
            for i, m in enumerate(root_moves):
                frm = m >> 7
                to = m & 127
                cap = board[to]
                k = board[frm]
                nh = h0 ^ ZK[k][frm] ^ ZK[k][to] ^ ZS
                board[frm] = EMPTY
                board[to] = k
                psq[k] = to
                nlc = 0
                if cap >= 0:
                    nh ^= ZK[cap][to]
                    psq[cap] = -1
                    cnt[1] -= 1
                    nlc = to
                if i == 0 or not USE_PVS:
                    s = -negamax(depth - 1, -beta, -a, 1, 1, nh, nlc)
                else:
                    s = -negamax(depth - 1, -a - 1, -a, 1, 1, nh, nlc)
                    if s > a and s < beta and beta - a > 1:
                        s = -negamax(depth - 1, -beta, -a, 1, 1, nh, nlc)
                board[to] = cap
                board[frm] = k
                psq[k] = frm
                if cap >= 0:
                    psq[cap] = to
                    cnt[1] += 1
                if stop[0]:
                    return best_s, best_m, False
                scores[m] = s
                if i == 0:
                    best_s = s
                    best_m = m
                    if s > a:
                        a = s
                elif s > a:
                    best_s = s
                    best_m = m
                    a = s
                if a >= beta:
                    break
            return best_s, best_m, True

        best_move = root_moves[0]
        best_score = 0
        prev_s = None
        last_dt = 0.0
        done_depth = 0
        for d in range(1, MAX_DEPTH + 1):
            el = time.process_time() - t_enter
            if d > 1 and (
                el > alloc * SOFT_TIME_FRACTION
                or el + last_dt * NEXT_ITER_FACTOR > alloc
            ):
                break
            it0 = time.process_time()
            ext_limit[0] = d + THREAT_EXT_PLY_MARGIN
            delta = ASP_DELTA
            if (
                USE_ASPIRATION
                and d >= ASP_START_DEPTH
                and prev_s is not None
                and abs(prev_s) < MATE_THRESH
            ):
                a = prev_s - delta
                b = prev_s + delta
            else:
                a = -INF
                b = INF
            finished = False
            while True:
                s, mv, ok = root_iter(d, a, b)
                if not ok:
                    if mv:
                        best_move = mv
                        best_score = s
                    break
                if s <= a and a > -INF:  # fail low: widen downwards
                    delta *= ASP_WIDEN
                    a = a - delta if delta < 3000 else -INF
                    continue
                if s >= b and b < INF:  # fail high: widen upwards
                    if mv in root_moves:
                        root_moves.remove(mv)
                        root_moves.insert(0, mv)
                    best_move = mv
                    delta *= ASP_WIDEN
                    b = b + delta if delta < 3000 else INF
                    continue
                best_move = mv
                best_score = s
                finished = True
                break
            if stop[0] or not finished:
                break
            prev_s = best_score
            done_depth = d
            last_dt = time.process_time() - it0
            root_moves.sort(
                key=lambda mm: (mm == best_move, scores.get(mm, -INF)), reverse=True
            )
            if best_score >= MATE_THRESH:  # forced win found: no need to look further
                break

        if DEBUG:
            print(
                "depth",
                done_depth,
                "score",
                best_score,
                "nodes",
                nodes[0],
                "time %.3f/%.3f" % (time.process_time() - t_enter, alloc),
                "tt",
                len(tt),
            )
        return finish(best_move)

    # =====================================================================
    # entry point: run the engine, fall back to greedy if anything breaks
    # =====================================================================
    try:
        result = search_move()
    except Exception as ex:
        # if DEBUG:
        #     print("ENGINE ERROR", repr(ex))
        result = fallback()
    memo["used"] = memo.get("used", 0.0) + (time.process_time() - t_enter)
    return result
