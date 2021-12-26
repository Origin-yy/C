#include <stdio.h>
#include <stdlib.h>
#define ROWS 20
#define COLS 30
#define LEVELS 10
#define LEN 50
const char trans[LEVELS + 1] = " .':~*=&%#"; //存储需要转换的字符;

int clean_distortion(int (*a)[COLS], int rows, int x, int y);
void change(int (*a)[COLS], char (*b)[COLS], int rows);

int main(void)
{
    int row, col;
    FILE *infile;
    char filename[LEN];
    int figure[ROWS][COLS];
    char picture[ROWS][COLS];

    printf("Please enter a filename: ");
    scanf("%49s", filename);

    if ((infile = fopen(filename, "r+")) == NULL)
    {
        fprintf(stderr, "Can't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            fscanf(infile, "%d", &figure[row][col]);
            //↑从文件中读取数字;
        }
    }
    if (ferror(infile))
    {
        fprintf(stderr, "Error getting data from file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            figure[row][col] = clean_distortion(figure, ROWS, row, col);
        }
    }
    change(figure, picture, ROWS);
    printf("File %s have been transformed pictures:\n", filename);
    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            putchar(picture[row][col]);
        }
        putchar('\n');
    }

    fseek(infile, 0L, SEEK_END); //定位到文件末尾;
    putc('\n', infile);          //↓将结果存储到文本文件中;
    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            fprintf(infile, "%c", picture[row][col]);
        }
        putc('\n', infile);
    }
    if (fclose(infile) != 0)
    {
        fprintf(stderr, "Can't close file %s\n", filename);
    }

    return 0;
}

int clean_distortion(int (*a)[COLS], int rows, int x, int y)
{
    int average; //用于四舍五入的中间局部变量;

    if (x == 0) //←矩形的上边
    {
        if (y == 0)
        {
            //↑矩形左上顶点;
            if ((a[x][y] - a[x][y + 1]) > 1 && (a[x][y] - a[x + 1][y]) > 1)
            {
                average = ((a[x][y + 1] + a[x + 1][y]) / 2.0 + 0.5); //四舍五入公式;
                return average;
            }
        }
        if (y == COLS - 1)
        {
            //↑矩形右上顶点;
            if ((a[x][y] - a[x][y - 1]) > 1 && (a[x][y] - a[x + 1][y]) > 1)
            {
                average = ((a[x][y - 1] + a[x + 1][y]) / 2.0 + 0.5);
                return average;
            }
        }
        //↓矩形的上边除了顶点之外的点;
        if ((a[x][y] - a[x][y - 1]) > 1 &&
            (a[x][y] - a[x][y + 1]) > 1 &&
            (a[x][y] - a[x + 1][y]) > 1)
        {
            average = ((a[x][y - 1] + a[x][y + 1] + a[x + 1][y]) / 3.0 + 0.5);
            return average;
        }
    }
    else if (x == rows - 1) //←矩形的下边
    {
        if (y == 0)
        {
            //↑矩形左下顶点;
            if ((a[x][y] - a[x - 1][y]) > 1 && (a[x][y] - a[x][y + 1]) > 1)
            {
                average = ((a[x - 1][y] + a[x][y + 1]) / 2.0 + 0.5);
                return average;
            }
        }
        if (y == COLS - 1)
        {
            //↑矩形右下顶点;
            if ((a[x][y] - a[x][y - 1]) > 1 && (a[x][y] - a[x - 1][y]) > 1)
            {
                average = ((a[x][y - 1] + a[x - 1][y]) / 2.0 + 0.5);
                return average;
            }
        }
        //↓矩形的下边除了顶点之外的点;
        if ((a[x][y] - a[x][y - 1]) > 1 &&
            (a[x][y] - a[x][y + 1]) > 1 &&
            (a[x][y] - a[x - 1][y]) > 1)
        {
            average = ((a[x][y - 1] + a[x][y + 1] + a[x - 1][y]) / 3.0 + 0.5);
            return average;
        }
    }
    if (y == 0) //←矩形的左边除了顶点之外的点;
    {
        if ((a[x][y] - a[x - 1][y]) > 1 &&
            (a[x][y] - a[x + 1][y]) > 1 &&
            (a[x][y] - a[x][y + 1]) > 1)
        {
            average = ((a[x - 1][y] + a[x + 1][y] + a[x][y + 1]) / 3.0 + 0.5);
            return average;
        }
    }
    else if (y == COLS - 1) //←矩形的右边除了顶点之外的点;
    {
        if ((a[x][y] - a[x - 1][y]) > 1 &&
            (a[x][y] - a[x + 1][y]) > 1 &&
            (a[x][y] - a[x][y - 1]) > 1)
        {
            average = ((a[x - 1][y] + a[x + 1][y] + a[x][y - 1]) / 3.0 + 0.5);
            return average;
        }
    }
    //↓矩形剩余所有的点;
    if ((a[x][y] - a[x - 1][y]) > 1 &&
        (a[x][y] - a[x + 1][y]) > 1 &&
        (a[x][y] - a[x][y - 1]) > 1 &&
        (a[x][y] - a[x][y + 1]) > 1)
    {
        average = ((a[x - 1][y] + a[x + 1][y] + a[x][y - 1] + a[x][y + 1]) / 4.0 + 0.5);
        return average;
    }
    return a[x][y]; //←以上条件都不符合则返回原值;
}

void change(int (*a)[COLS], char (*b)[COLS], int rows)
{
    int row, col;

    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            b[row][col] = trans[a[row][col]];
            //↑进行数字对应的字符转换;
        }
    }
    return;
}
