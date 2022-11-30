#include <stdio.h>

#define MAZE_ROW    5      //���H�̍s��
#define MAZE_COLUMN 5      //���H�̗�

//�v���C���[
typedef struct
{
    int row;        //�v���C���[�ʒu(�s)
    int column;     //�v���C���[�ʒu(��)
}MazePlayer;


//���H�̈�u���b�N
enum MazeKind { PATH, WALL, START, GOAL };    //�u���b�N�̎��(���A�ǁA�X�^�[�g�A�S�[��)
enum MazeFlag { FALSE, TRUE };                //�u���b�N���������Ă��邩�ǂ���

typedef struct
{
    enum MazeKind kind;            //���(���A�ǁA�X�^�[�g�A�S�[��)
    enum MazeFlag flag;            //�u���b�N���������Ă��邩�ǂ���
} MazeBlock;


//�v���C���[������
int MazePlayerInit(int* playerRow, int* playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
    int i, j;

    for (i = 0; i < MAZE_ROW; i++) //�s
    {
        for (j = 0; j < MAZE_COLUMN; j++) //��
        {
            if (maze[i][j].kind == START) //�X�^�[�g�n�_�Ȃ�΃v���C���[�̈ʒu�ɐݒ肷��
            {
                *playerRow = i;
                *playerColumn = j;
                return 0; //�֐��I��(�v���C���[��ݒ�ł���Ύc��̏����͕K�v�Ȃ�)
            }
        }
    }

    //�X�^�[�g�n�_���Ȃ���΁A�v���C���[��ݒ�ł��������܂ł���
    printf("�X�^�[�g������܂���\n");
    return -1;
}

//���H�\��
void MazeDraw(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
    int i, j;

    for (i = 0; i < MAZE_ROW; i++) //�s
    {
        for (j = 0; j < MAZE_COLUMN; j++) //��
        {
            if (i == playerRow && j == playerColumn) //�v���C���[�ʒu
            {
                printf("�o");
            }
            else if (maze[i][j].flag == FALSE) //�u���b�N���������Ă��Ȃ��ꍇ
            {
                printf("�H");
            }
            else
            {
                switch (maze[i][j].kind)
                {
                case WALL:
                    printf("��"); break; //��
                case GOAL:
                    printf("�f"); break; //�S�[��
                default:
                    printf("�@"); break; //���̑�(���A�X�^�[�g)
                }
            }
        }
        printf("\n");
    }
}


int main(void)
{
    //�v���C���[
    MazePlayer player;

    //���H
    MazeBlock maze[MAZE_ROW][MAZE_COLUMN] =
    {
      { {START, TRUE } , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
      { {WALL , FALSE} , {WALL , FALSE}, {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
      { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
      { {PATH , FALSE} , {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
      { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {GOAL , TRUE } },
    };

    //�v���C���[������
    if (MazePlayerInit(&player.row, &player.column, maze) == -1)
    {
        //�֐�MazePlayerInit��-1��Ԃ��Ƃ��������Ɏ��s���Ă���
        //����āA���̎��_�Ńv���O�������I�����A���H�̕\���͍s��Ȃ�
        return 0;
    }

    //���H�\��
    MazeDraw(player.row, player.column, maze);

    return 0;
}