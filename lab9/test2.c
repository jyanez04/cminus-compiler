int addNums(int a, int b)
{
    write a;
    write "\n";
    write b;
    write "\n";
    return a + b;
}

void writeSomething(void)
{
    write "function call worked for now...\n";
}

int main(void)
{
    int total;
    int x;
    int y;
    
    read x;
    write x;
    write "\n\n";

    read y;
    write y;
    write "\n\n";
    
    total = addNums(x, y) + addNums(10, 10);
    

    write total;
    write "\n";

    write 1;
    write "\n";

    writeSomething();

}

