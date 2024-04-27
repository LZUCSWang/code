# include <stdio.h>
# include <stdlib.h>
int main(int argc , char * argv[])
{
	FILE * in , * out ;
	char ch ;
	size_t byt ;
	if (argc != 3)
	{
		fprintf(stderr , "错误的参数.\n");
		exit(EXIT_FAILURE);
	}
	if ((in = fopen(argv[1] , "rb")) == NULL)
	{
		fprintf(stderr , "打不开文件%s.\n" , argv[1]);
		exit(EXIT_FAILURE);
	}
	if ((out = fopen(argv[2] , "wb")) == NULL)
	{
		fprintf(stderr , "打不开文件%s.\n" , argv[2]);
		exit(EXIT_FAILURE);
	}
	while ((byt = fread(&ch , sizeof(ch) , 1 , in)) && !feof(in))
		fwrite(&ch , sizeof(ch) ,1 , out);
	if (fclose(in) || fclose(out))
	{
		fprintf(stderr , "退出失败.\n");
		exit(EXIT_FAILURE);
	}
	return 0 ;
}
