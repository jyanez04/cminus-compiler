int x;
int A[100];

int addNums(int a, int b)
{
    return a + b;
}

int main(void)
{
    int nums[4];
    int B[5];
    int z;
    int y;
    int i;
    int total;
    i = 0;
    nums[0] = 6;
    nums[1] = 0;
    nums[2] = 3;
    nums[3] = 5;

    A[5] = 125;
    A[0] = 34;
    total = addNums(A[5], A[0]);
    write total;
    write "\n";

    A[34] = 200;
    B[2] = A[0] + 2 * A[0];
    write A[5];
    write "\n";
    write A[0];
    write "\n";
    write B[2];
    write "\n";
    write A[A[0]];
    write "\n";
    z = 137;
    write z;
    write "\n";

    while (i < 10)
    {
        if (i % 2 == 0)
        {
            write "even: ";
            write i;
            write "\n";
        }
        else
        {
            write "odd: ";
            write i;
            write "\n";
        }
        i = i + 1;
    }
}