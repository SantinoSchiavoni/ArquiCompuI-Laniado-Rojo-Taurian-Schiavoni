
#include <string.h>
#include <stdio.h>
#include "EasyPIO.h"
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

const char led []={14,15,18,23,24,25,8,7};


int delay_controlado(int tiempo, int *tiempo_ref)
{
    struct termios oldt, newt;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int transcurrido = 0;
    int paso = 10;

    while (transcurrido < tiempo)
    {
        int ch = getchar();
        if (ch == 27) // ESC o secuencia de tecla especial
        {
            int ch1 = getchar();
            if (ch1 == -1)
            {
                // ESC solo → salir
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                fcntl(STDIN_FILENO, F_SETFL, oldf);
                return 1;
            }
            int ch2 = getchar();
            if (ch1 == 91)
            {
                if (ch2 == 65) // ↑
                {
                    *tiempo_ref = (*tiempo_ref > 50) ? *tiempo_ref - 50 : *tiempo_ref;
                    fflush(stdout);
                }
                else if (ch2 == 66) // ↓
                {
                    *tiempo_ref += 50;
                    fflush(stdout);
                }
            }
        }

        delayMillis(paso * 1000);
        transcurrido += paso;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    return 0;
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
            char c = getchar();
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

int choqueLuces(int *tiempo)
{
    unsigned char bits[8] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
    for (int i = 0; i < 8; i++)
    {
        disp_binary(bits[i]);
        if (delay_controlado(*tiempo, tiempo))
        {
            return 1; // ESC presionado
        }
    }
    return 0; // No se presionó ESC
}

int autofan(int *tiempo)
{
    unsigned int c = 0x80;

    for (int i = 0; i < 7; i++)
    {
        disp_binary(c);
        if (delay_controlado(*tiempo, tiempo))
        {
            return 1; // ESC presionado
        }
        c = c >> 1;
    }

    for (int i = 0; i < 8; i++)
    {
        disp_binary(c);
        if (delay_controlado(*tiempo, tiempo))
        {
            return 1; // ESC presionado
        }
        c = c << 1;
    }
    return 0; // No se presionó ESC
}

int leds(int num){
    int numval;
    for (int i = 0; i < 8; i++)
    {
        numval=(num>>i) & 0x01;
        digitalWrite(led[i],numval);
    }
    return 0;
    }
    


extern int pulso2(int *tiempo_ptr);

int main()
{
    pioInit();

    for (int i = 0; i < 8; i++)
    {
        pinMode(led[i],OUTPUT);
    }
    leds(0xFF);
    
    

    if (!Login())
    {
        printf("Acceso denegado.");
        printf("\n");
        return 0;
    }
    else
    {
        printf("Acceso concedido.\n");
        printf("Bienvenido al sistema.\n");
    }

    int opcion;
    int tiempo = 500;
    do
    {

        menu();
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
                do {
                }while (!choqueLuces(&tiempo));
            break;
        case 2:
                do {
                }while (!autofan(&tiempo));
            break;
        case 3:
            do{}
            while(!pulso2(&tiempo));
    

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