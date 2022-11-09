#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#define ppp ft_printf

int ft_printstr(char *s)
{
    int i = 0;
    if (s == NULL)
        return (write(1, "(error)", 7));
    while(s[i])
        i++;
    return (write(1, s, i));        
}

int ft_printddd(int n, char *base)
{
    int i;
    char c;

    i = 0;
    if(n == INT_MIN)
        return write(1, "-2147483648", 11);
    if (n < 0)
     {
        n = -n;
        i += write(1, "-", 1);
     }
     if (n > 9)
        i += ft_printddd(n / 10, base);
    c = base[n % 10];
    i += write(1, &c, 1);
    return (i);
}

int ft_printhhh(unsigned int n, char *base)
{
    int i;
    char c;

    i = 0;
     if (n > 15)
        i += ft_printhhh(n / 16, base);
    c = base[n % 16];
    i += write(1, &c, 1);
    return (i);
}

int ppp(char *format, ...)
{
    va_list l;
    int i, len;
    i = len = 0;

    va_start(l, format);
    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 's')
                len += ft_printstr(va_arg(l, char *));
            if (format[i] == 'd')
                len += ft_printddd(va_arg(l, int), "0123456789");
            if (format[i] == 'x')
                len += ft_printhhh(va_arg(l, unsigned int), "0123456789abcdef");
            if (format[i] == '%')
                len += write(1, &format[i], 1);
            i++;
        }
        else{
            len += write(1, &format[i], 1);
            i++;
        }
    }
    va_end(l);
    return (len);

}

int main()
{
    printf("%d\n", printf("%% %%%% %%%%%%\n"));
    printf("%d\n", ppp("%% %%%% %%%%%%\n"));
    printf("%d\n", printf("%d\n", INT_MAX));
    printf("%d\n", ppp("%d\n", INT_MAX));
    printf("%d\n", printf("%d\n", INT_MIN));
    printf("%d\n", ppp("%d\n", INT_MIN));
    printf("%d\n", printf("%x\n", INT_MAX));
    printf("%d\n", ppp("%x\n", INT_MAX));
    printf("%d\n", printf("%x\n", INT_MIN));
    printf("%d\n", ppp("%x\n", INT_MIN));
    return 0;
}
