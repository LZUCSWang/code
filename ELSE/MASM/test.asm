DATA SEGMENT                        ;//�������ݶ�
    MYWORD DB "hello world!!!!$"    ;//�����ַ�������
DATA ENDS

CODE SEGMENT                        ;//��������
          ASSUME CS:CODE,DS:DATA    ;//˵������������ݶ�
    start:
          MOV    AX,DATA            ;//��DATA(�����׵�ַ)->AX�Ĵ���
          MOV    DS,AX              ;//ʹ��DS����AX
          LEA    DX,MYWORD          ;//ʹ��DX����MYWORD���׵�ַ
          MOV    AH,09h             ;//AH�������
          INT    21h                ;//ִ��AH��09h���ܣ����
          MOV    AX,4c00h           ;//���üĴ�������
          INT    21h                ;//���üĴ������ܣ���������
CODE ENDS

END start;��ʾ��start��ִ�г��򣬲���������
