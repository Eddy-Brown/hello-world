#include <fstream>

int main()
{
    std::ofstream outFile;
    //打开文件
    outFile.open("D:\\Test.txt");
    int arr[5] = {1, 2, 3, 4, 5};
    int i;
    for(i = 0; i < 5; i++)
    {
        //写入数据
        outFile << arr[i];
    }
    //关闭文件
    outFile.close();
}

