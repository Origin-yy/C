int main()
{
	char ch = 0;
	while ((ch = getchar()) != '#')
	{
		 if (ch >= 'A' && ch <= 'Z')
		{
			ch += 32;
			printf("%c",ch);
		}
		else if (ch >= 'a' && ch <= 'z')
		{
			ch -= 32;
			printf("%c",ch);
		}
        else
        {
            printf("%c",ch);
        }
	}
	return 0;
}
