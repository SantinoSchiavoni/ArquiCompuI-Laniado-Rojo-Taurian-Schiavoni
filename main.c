
#include <string.h>
#include <stdio.h>

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// Función para detectar si se presionó una tecla
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Guardar configuración actual del terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Desactivar el modo canónico y el eco
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Establecer stdin como no bloqueante
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    // Restaurar configuración del terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin); // Devolver el carácter al buffer
        return 1;
    }

    return 0;
}

void delay(int *a)
{
    int i;
    unsigned int j = 0x2fffff;
    for (i = 0; i < *a; i++)
    {
        for (j = 0; j < 70000; j++)
        {
            // Simulate a delay
        }
    }
}

void menu()
{
    printf("MENU");
    printf("\n1. Choque Luces");
    printf("\n2. Autofan");
    printf("\n3. Opcion 3");
    printf("\n0. Salir");

    printf("\n");
}

int Login()
{
    int intentos = 0;
    int cantidad_caracteres = 5;
    char password_ingresado[6] = {0};

    do
    {
        intentos++;
        printf("Ingrese la contrasena (5 caracteres): ");

        for (int i = 0; i < cantidad_caracteres; i++)
        {
            char c = getch();
            password_ingresado[i] = c;
            printf("*"); // Mostrar asterisco en lugar del caracter
        }
        password_ingresado[cantidad_caracteres] = '\0'; // null-terminate

        printf("\n");

        if (strcmp(password_ingresado, "12345") == 0)
        {
            return 1;
        }
        else
        {
            printf("Contrasenia incorrecta, le quedan: ");
            printf("%d intentos", 3 - intentos);
            printf(".\n");
        }

    } while (intentos < 3);

    printf("Demasiados intentos fallidos.");
    return 0;
}

void disp_binary(int i)
{
    int t;
    for (t = 128; t > 0; t = t / 2)
        if (i & t)
            printf("*");
        else
            printf("_");
    printf("\n");
}

void choqueLuces()
{
    static int tiempo = 2000;

    unsigned char bits[8] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
    for (int i = 0; i < 8; i++)
    {
        // system("cls"); // Clear the console
        disp_binary(bits[i]);
        delay(&tiempo);
    }
}

void autofan()
{
    printf("Autofan activado.\n");
    static int tiempo = 2000;
    unsigned int c = 0x80;

    for (int i = 0; i < 7; i++)
    {
        // system("cls"); // Clear the console
        disp_binary(c);
        delay(&tiempo);
        c = c >> 1;
    }

    for (int i = 0; i < 8; i++)
    {
        disp_binary(c);
        delay(&tiempo);
        c = c << 1;
    }
}

int main()
{

    if (!Login())
    {
        printf("Acceso denegado.");
        printf("\n");
        return 0;
    }
    else
    {
        printf("Acceso concedido.\n");
    }

    int opcion;

    do
    {
        menu();
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            choqueLuces();
            break;
        case 2:
            autofan();
            break;
        case 3:
            do
            {
                printf(" probando");
                // pulso2();
            } while (!getchar());
            ;
            break;
        case 0:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opcion no valida, intente de nuevo.\n");
            break;
        }
    } while (opcion != 0);
}
