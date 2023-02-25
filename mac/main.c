#include "main.h"
#include <sys/param.h>

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

char *own_strjoin(char const *s1, char const *s2)
{
    char *result;
    char *temp;

    temp = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
    if (!temp)
        return (0);
    result = temp;
    while (*s1)
        *(temp++) = *(s1++);
    while (*s2)
        *(temp++) = *(s2++);
    *temp = '\0';
    return (result);
}

int main(int argc, char **argv)
{
    char **all_string = (char **)malloc(1024);
    char **result = (char **)malloc(1024);
    char *line;
    int fd;
    int i = 0;
    char resolved_path[MAXPATHLEN];

    realpath(argv[0], resolved_path);
    printf("resolved_path: %s\n", own_strjoin(resolved_path, "_result/text.txt"));

    if (!(fd = open(own_strjoin(resolved_path, "_result/text.txt"), O_RDONLY))) // 1
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

    fd2 = open(own_strjoin(resolved_path, "_result/result.txt"), O_WRONLY | O_CREAT, 0644);
    while (result[k])
    {
        write(fd2, result[k], strlen(result[k]));
        write(fd2, "\n", 1);
        k++;
    }
    close(fd2);

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