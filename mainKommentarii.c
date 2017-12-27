 
#include <stdio.h>
#include <assert.h>

/* удаляет многострочные и однострочные комментарии из файла
   комментарии в двойных кавычках не рассматривает */
int main(void)
{
    FILE *ifp, *ofp;
    int c, s;
    
    ifp = fopen("in.txt", "rb");
    ofp = fopen("out.txt", "wb");
    
    assert(ifp && ofp && "open files");
    
    s = 0;
    while ((c = getc(ifp)) != EOF)
        switch (s) {
            case 0:
                if (c == '/')
                    s = 1;
                else if (c == '\"') {
                    s = 5;
                    putc(c, ofp);
                } else
                    putc(c, ofp);
                break;
            case 1:
                if (c == '*')
                    s = 2;
                else if (c == '/')
                    s = 4;
                else {
                    putc('/', ofp);
                    putc(c, ofp);
                }
                break;
            case 2:
                if (c == '*')
                    s = 3;
                break;
            case 3:
                if (c == '*')
                    ;
                else if (c == '/')
                    s = 0;
                else
                    s = 2;
                break;
            case 4:
                if (c == '\n')
                    s = 0;
                break;
            case 5:
                if (c == '\\')
                    s = 6;
                else if (c == '\"')
                    s = 0;
                putc(c, ofp);
                break;
            case 6:
                /* какое-нибудь неправильное экранирование ? можно проверить */
                putc(c, ofp);
                s = 5;
                break;
        }
        
    /* getc(ofp); */
    
    assert(!ferror(ifp) && !ferror(ofp) && "read write error");
    
    fclose(ifp);
    fclose(ofp);
    
    return 0;
}
