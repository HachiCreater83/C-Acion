#include <stdio.h>

#define MAZE_ROW    5      //迷路の行数
#define MAZE_COLUMN 5      //迷路の列数

//プレイヤー
typedef struct
{
    int row;        //プレイヤー位置(行)
    int column;     //プレイヤー位置(列)
}MazePlayer;


//迷路の一ブロック
enum MazeKind { PATH, WALL, START, GOAL };    //ブロックの種類(道、壁、スタート、ゴール)
enum MazeFlag { FALSE, TRUE };                //ブロックが判明しているかどうか

typedef struct
{
    enum MazeKind kind;            //種類(道、壁、スタート、ゴール)
    enum MazeFlag flag;            //ブロックが判明しているかどうか
} MazeBlock;


//プレイヤー初期化
int MazePlayerInit(int* playerRow, int* playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
    int i, j;

    for (i = 0; i < MAZE_ROW; i++) //行
    {
        for (j = 0; j < MAZE_COLUMN; j++) //列
        {
            if (maze[i][j].kind == START) //スタート地点ならばプレイヤーの位置に設定する
            {
                *playerRow = i;
                *playerColumn = j;
                return 0; //関数終了(プレイヤーを設定できれば残りの処理は必要ない)
            }
        }
    }

    //スタート地点がなければ、プレイヤーを設定できずここまでくる
    printf("スタートがありません\n");
    return -1;
}

//迷路表示
void MazeDraw(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
    int i, j;

    for (i = 0; i < MAZE_ROW; i++) //行
    {
        for (j = 0; j < MAZE_COLUMN; j++) //列
        {
            if (i == playerRow && j == playerColumn) //プレイヤー位置
            {
                printf("Ｐ");
            }
            else if (maze[i][j].flag == FALSE) //ブロックが判明していない場合
            {
                printf("？");
            }
            else
            {
                switch (maze[i][j].kind)
                {
                case WALL:
                    printf("口"); break; //壁
                case GOAL:
                    printf("Ｇ"); break; //ゴール
                default:
                    printf("　"); break; //その他(道、スタート)
                }
            }
        }
        printf("\n");
    }
}


int main(void)
{
    //プレイヤー
    MazePlayer player;

    //迷路
    MazeBlock maze[MAZE_ROW][MAZE_COLUMN] =
    {
      { {START, TRUE } , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
      { {WALL , FALSE} , {WALL , FALSE}, {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
      { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
      { {PATH , FALSE} , {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
      { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {GOAL , TRUE } },
    };

    //プレイヤー初期化
    if (MazePlayerInit(&player.row, &player.column, maze) == -1)
    {
        //関数MazePlayerInitが-1を返すとき初期化に失敗している
        //よって、この時点でプログラムを終了し、迷路の表示は行わない
        return 0;
    }

    //迷路表示
    MazeDraw(player.row, player.column, maze);

    return 0;
}