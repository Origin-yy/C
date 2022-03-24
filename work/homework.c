//是否有-a(即filenames中的.和..是否打印)
    if (!(flag & A))
    {
        for (i = 0; i < count; i++)
            if (filenames[i][0] != '.')
            {
                if (flag & L)
                    disply_file_l(filenames[i]);
                else
                    disply_file_only(filenames[i]);
            }
    }
    else
    {
        for (i = 0; i < count; i++)
        {
            if (flag & L)
                disply_file_l(filenames[i]);
            else
                disply_file_only(filenames[i]);
        }
    }