#include <fstream>

int main()
{
    std::ofstream outFile;
    //���ļ�
    outFile.open("D:\\Test.txt");
    int arr[5] = {1, 2, 3, 4, 5};
    int i;
    for(i = 0; i < 5; i++)
    {
        //д������
        outFile << arr[i];
    }
    //�ر��ļ�
    outFile.close();
}

