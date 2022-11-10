#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#define pr ft_printf

int ft_s(char *);
int ft_i(int);
int ft_x(unsigned int, int, char *);

int pr(char *format, ...)
{
    int i = 0, len = 0;

    va_list l;
    va_start(l, format);
    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == '%')
                len += write(1, &format[i], 1);
            if (format[i] == 's')
                len += ft_s(va_arg(l, char *));
            if (format[i] == 'd')
                len += ft_i(va_arg(l, int));
            if (format[i] == 'x')
                len += ft_x(va_arg(l, unsigned int), 16, "0123456789abcdef");
        }
        else
            len += write(1, &format[i], 1);
        i++;
    }
    va_end(l);
    return len;
}

int ft_s(char *s)
{
    int strlen = 0;
    
    if (!*s)
        return (write(1, "(null)", 6));
    while(s[++strlen]) ;
    return (write(1, s, strlen));
}

int ft_x(unsigned int n, int base, char *s_base)
{
    int i = 0;
    char c;
    if (n > (unsigned int) base - 1)
        i += ft_x(n / base, base, s_base);
    c = s_base[n % base];
    i += write(1, &c, 1);
    return i;
}

int ft_i(int n)
{
    int i = 0;

    if (n == -2147483648)
        return write(1, "-2147483648", 11);
    else if (n < 0)
    {
        n = -n;
        i += write(1, "-", 1);
    }
    i += ft_x(n, 10, "0123456789");
    return i;
}

int main()
{
    printf("%d\n", INT_MIN);
    printf("%d\n", printf("Hello, World!"));
    printf("%d\n", ft_printf("Hello, World!"));
    printf("%d\n", printf("%s", "Hello, World!"));
    printf("%d\n", ft_printf("%s", "Hello, World!"));
    printf("%d\n", printf("%s", "%% %%%% %%%%%%"));
    printf("%d\n", ft_printf("%s", "%% %%%% %%%%%%"));
    printf("%d\n", printf("%% %%%% %%%%%%"));
    printf("%d\n", printf("%% %%%% %%%%%%"));
    printf("%d\n", printf("%x\n", INT_MAX));
    printf("%d\n", ft_printf("%x\n", INT_MAX));
    printf("%d\n", printf("%d\n", INT_MAX));
    printf("%d\n", ft_printf("%d\n", INT_MAX));
    printf("%d\n", printf("%d\n", INT_MIN));
    printf("%d\n", ft_printf("%d\n", INT_MIN));
    printf("%d\n", printf("%d\n", 0));
    printf("%d\n", ft_printf("%d\n", 0));
    printf("%d\n", printf("%d\n", INT_MIN + 1));
    printf("%d\n", ft_printf("%d\n", INT_MIN + 1));
    return 0;
}
