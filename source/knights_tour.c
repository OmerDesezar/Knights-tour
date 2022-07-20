/*=========================== LIBRARIES & MACROS ============================*/

#include <assert.h> /* assert */
#include <time.h>   /* time */
#include "knights_tour.h"
#include "bitarray.h"

#define BOARD_LEN 8
#define MOVE_COUNT 8
#define BOARD_SIZE 64
#define INVALID_MOVE 65
#define TIMEFRAME 300

#define GET_POS_INDEX(x, y) ((BOARD_LEN * (y)) + (x))
#define IS_VISITED(board, pos) (BitArrayGetVal(board, pos))
#define IS_MOVE_IN_BOARD(x, y) (0 < (x + 1) && BOARD_LEN > (x) && 0 < (y + 1) && BOARD_LEN > (y))
#define NUM_OF_VISITS(board) (BitArrayCountOnNoLoop(board))

/*============================== DECLARATIONS ===============================*/

static void InitLut(int lut[BOARD_SIZE][MOVE_COUNT], int);
static void UpdateProgress(bitarray_t *, unsigned char *, int);
static void InsertionSort(int *, int move_lut[BOARD_SIZE][MOVE_COUNT], int);
static void SortByNumOfMoves(int, int move_lut[BOARD_SIZE][MOVE_COUNT], bitarray_t);
static return_status_t DoKnightsTour(unsigned char, unsigned char, unsigned char *, int);
static return_status_t KnightsTourRec(unsigned char, bitarray_t, unsigned char *, int move_lut[BOARD_SIZE][MOVE_COUNT], time_t, int);

/*========================== FUNCTION DEFINITION ============================*/

return_status_t KnightsTour(unsigned char x_pos, unsigned y_pos, unsigned char *path)
{
    return (DoKnightsTour(x_pos, y_pos, path, 0));
}

return_status_t WarnsdorffKnightsTour(unsigned char x_pos, unsigned char y_pos, unsigned char *path)
{
    return (DoKnightsTour(x_pos, y_pos, path, 1));
}

static return_status_t DoKnightsTour(unsigned char x_pos, unsigned char y_pos, unsigned char *path, int warnsdorff)
{
    bitarray_t board = 0;
    static int move_lut[BOARD_SIZE][MOVE_COUNT];
    unsigned char start_pos = GET_POS_INDEX(x_pos, y_pos);

    assert(NULL != path);
    assert(IS_MOVE_IN_BOARD(x_pos, y_pos));

    InitLut(move_lut, warnsdorff);
    return (KnightsTourRec(start_pos, board, path, move_lut, time(0), warnsdorff));
}

static return_status_t KnightsTourRec(unsigned char curr_pos,
                                      bitarray_t board, unsigned char *path, int move_lut[BOARD_SIZE][MOVE_COUNT], time_t start_time, int warnsdorff)
{
    int move = 0;

    if (TIMEFRAME <= (time(0) - start_time))
    {
        return (TIMEOUT);
    }
    UpdateProgress(&board, path, curr_pos);
    if (BOARD_SIZE == NUM_OF_VISITS(board))
    {
        return (TRUE);
    }
    if (warnsdorff)
    {
        SortByNumOfMoves(curr_pos, move_lut, board);
    }

    for (move = 0; move < MOVE_COUNT; ++move)
    {
        int next_pos = move_lut[curr_pos][move];
        if (INVALID_MOVE != next_pos && !IS_VISITED(board, next_pos))
        {
            return_status_t status = KnightsTourRec(next_pos, board, path + 1, move_lut, start_time, warnsdorff);
            if (FALSE != status)
            {
                return (status);
            }
        }
    }
    return (FALSE);
}

static void SortByNumOfMoves(int curr_pos, int move_lut[BOARD_SIZE][MOVE_COUNT], bitarray_t board)
{
    int i = 0, j = 0;
    int count_arr[MOVE_COUNT] = {0};
    for (i = 0; i < MOVE_COUNT; ++i)
    {
        int next_pos = move_lut[curr_pos][i];
        if (INVALID_MOVE == next_pos || IS_VISITED(board, next_pos))
        {
            count_arr[i] = INVALID_MOVE;
            continue;
        }
        for (j = 0; j < MOVE_COUNT; ++j)
        {
            int next_next = move_lut[next_pos][j];
            if (INVALID_MOVE != next_next && !IS_VISITED(board, next_next))
            {
                ++count_arr[i];
            }
        }
    }
    InsertionSort(count_arr, move_lut, curr_pos);
}

static void InsertionSort(int *count_arr, int move_lut[BOARD_SIZE][MOVE_COUNT], int curr_pos)
{
    int i = 0, j = 0, key = 0, key2 = 0;
    for (i = 1; i < MOVE_COUNT; ++i)
    {
        key = count_arr[i];
        key2 = move_lut[curr_pos][i];
        j = i - 1;
        while (count_arr[j] > key && 0 <= j)
        {
            count_arr[j + 1] = count_arr[j];
            move_lut[curr_pos][j + 1] = move_lut[curr_pos][j];
            j--;
        }
        count_arr[j + 1] = key;
        move_lut[curr_pos][j + 1] = key2;
    }
}

static void InitLut(int lut[BOARD_SIZE][MOVE_COUNT], int warnsdorff)
{
    static int is_initialized = 0;
    if (!warnsdorff || !is_initialized)
    {
        char x_moves[MOVE_COUNT] = {2, 1, -1, -2, -2, -1, 1, 2};
        char y_moves[MOVE_COUNT] = {1, 2, 2, 1, -1, -2, -2, -1};
        int x = 0, y = 0, move = 0;
        for (; y < BOARD_LEN; ++y)
        {
            for (x = 0; x < BOARD_LEN; ++x)
            {
                for (move = 0; move < MOVE_COUNT; ++move)
                {
                    int x_moved = x + x_moves[move];
                    int y_moved = y + y_moves[move];
                    lut[GET_POS_INDEX(x, y)][move] = (IS_MOVE_IN_BOARD(x_moved, y_moved)) ? GET_POS_INDEX(x_moved, y_moved) : INVALID_MOVE;
                }
            }
        }
        is_initialized = 1;
    }
}

static void UpdateProgress(bitarray_t *board, unsigned char *path, int pos)
{
    *board = BitArraySetOn(*board, pos);
    *path = pos;
}