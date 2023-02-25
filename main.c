#include "main.h"

int get_start_idx(const char *haystack, const char *needle)
{
    int i = 0;
    int j = 0;

    while (haystack[i] != '\n' && haystack[i] != '\0')
    {
        while (haystack[i + j] == needle[j] && haystack[i + j] != '\n' && haystack[i + j] != '\0' && needle[j] != '\0')
            j++;
        if (needle[j] == '\0')
            return (i);
        j = 0;
        i++;
    }
    return (-1);
}

int main()
{
    char **all_string = (char **)malloc(1024);
    char **result = (char **)malloc(1024);
    char *line;
    int fd;
    int i = 0;

    if (!(fd = open("text.txt", O_RDONLY))) // 1
    {
        printf("\nError in open");
        return (0);
    }
    while (line = get_next_line(fd)) // 2
    {
        line[ft_strlen(line) - 1] = '\0';
        all_string[i] = line;
        i++;
    }
    all_string[i] = NULL;
    printf("\n");
    i = 0;

    int j = 0;
    int k = 0;

    while (all_string[i])
    {
        if (get_start_idx(all_string[i], "shift started by") != -1)
        {
            result[k++] = all_string[i];
            while (all_string[i] && get_start_idx(all_string[i], "shift ended by") == -1)
            {
                if (get_start_idx(all_string[i], "4eye check") != -1)
                {
                    j = i;
                    while (j >= 0)
                    {
                        if (all_string[j][0] >= 48 && all_string[j][0] <= 57)
                        {
                            result[k++] = all_string[j];
                            break;
                        }
                        j--;
                    }
                    result[k++] = all_string[i];
                    j = 0;
                }
                i++;
            }
        }
        i++;
    }
    result[k] = NULL;
    k = 0;

    int fd2;

    if (0 < (fd2 = open("result.txt", O_WRONLY | O_CREAT | O_EXCL, 0644)))
    {
        while (result[k])
        {
            write(fd2, result[k], strlen(result[k]));
            write(fd2, "\n", 1);
            k++;
        }
        close(fd2);
    }
    else
    {
        printf("파일이 이미 존재합니다.\n");
    }

    k = 0;

    while (all_string[k])
    {
        free(all_string[k]);
        all_string[k] = NULL;
    }
    free(all_string);
    all_string = NULL;

    close(fd); // 5

    return (0);
}