#include <conio.h>
#include <string.h>
#include <stdio.h>

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
    printf("\n2. Opcion 2");
    printf("\n3. Opcion 3");

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
        system("cls"); // Clear the console
        disp_binary(bits[i]);
        delay(&tiempo);
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
            printf("Opcion 2 seleccionada.\n");
            break;
        case 3:
            printf("Opcion 3 seleccionada.\n");
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
