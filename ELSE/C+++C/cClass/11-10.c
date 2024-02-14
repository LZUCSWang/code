    #include <stdio.h>
    #include <string.h>
    void removekong(char *str)
    {
        int right = 0, left = 0;
        while (str[right] != '\0')//�����ַ���
        {
            while (str[right] == ' ')//���ұ���ָ���Ϊ�ո�ʽ���ұߵ�����֪�����ǿո�
                right++;
            str[left] = str[right];//���ұߵĸ������
            left++, right++;
        }
    }
    int main()
    {
        char input[10], cnt[100];
        int k = 0;
        fgets(input, 9, stdin);//ѭ����ȡ����
        while (input[0] != '\n')//������Ϊֱ��һ�����У�ֱ���˳�ѭ��
        {
            removekong(input);//���������ַ���
            for (int i = 0; i < strlen(input); i++)
            {
                cnt[k++] = input[i];
            }
            fgets(input, 9, stdin);
        }
        printf("%s", cnt);//�����������ַ�
    }