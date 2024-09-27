#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#pragma warning(disable:4996)

// Clear C6031 (Return scanf)
#pragma warning(disable:6031)

// Staff Data
typedef struct{
    char ID_Staff[21];          // 2303484
    char Name_Staff[31];        // MR ON
    char Password_Staff[21];    // 123456789Abc
    char RePass_Staff[7];       // Tm080t
} staff;

// To create NEW Staff
staff NEW;

// Staff that already login
staff Staff1;

// Admin Data
typedef struct{
    char ID_Admin[21];          // 2303484
    char Name_Admin[31];        // MR ON
    char Password_Admin[21];    // 123456789Abc
    char RePass_Admin[7];       // Tm080t
} admin;

// Admin that already login
admin Admin1;

// Data Example Admin
// admin Admin1 = {2303484 , "ON YUEN SHERN" , "123456789Abc" , "Tm080t"};

// History Admin
typedef struct{
    char admin_id[21];           // 2303484
    char timeCheck[20];     // HH:MM:SS dd/mm/yyyy
    char event_type[8];     // "LOGIN" or "LOGOUT"
} AdminHistory;

// History Admin
typedef struct{
    char staff_id[21];           // 2303484
    char timeCheck[20];     // HH:MM:SS dd/mm/yyyy
    char event_type[8];     // "LOGIN" or "LOGOUT"
} StaffHistory;

// Clear C4013
void header();
char* timeF();
int staff_menu();
int login_staff();
int admin_menu();
int login_admin();
int readFile(const char* filetype, const char* login_id, const char* login_password); int admin_LoginHistory();
int admin_LoginHistory();
int staff_LoginHistory();
int staff_page();
int staff_SignoutHistory();
int staff_history();
int staff_details_page();
int edit_staff_process(int edit_type);
int staff_forget_password();
int find_staff_forget_process(char* StaffID_Forget, char* Staff_RePass);
int staff_forget_process(char* StaffID_Forget, char* Staff_NewPass);
int admin_page();
int admin_staff_management_page();
int admin_SignoutHistory();
int admin_history();
int create_new_staff();
int check_staff_id();
int staff_create_process();
int delete_staff_page();
int delete_staff_process(char* delete_staff_id);
int confirm_delete_Staff_process(char* delete_staff_id);
int display_all_staff();
int search_staff_process(char* search_staff);
int staff_details(char* search_staff);
int admin_edit_staff_process(char* search_staff, int edit_type);
int edit_staff_details(char* search_staff);
int admin_details_page();
int edit_admin_process(int edit_type);
int admin_forget_password();
int find_admin_forget_process(char* AdminID_Forget, char* Admin_RePass);
int admin_forget_process(char* AdminID_Forget, char* Admin_NewPass);
int create_admin_page();
int auto_create_admin();

// Header Logo
void header() {
    // clean screen
    system("cls");

    // Header
    printf("======================================================================================= \n");
    printf("  _____   ____       _      ___   _   _     _____   ___    ____   _  __  _____   _____ \n");
    printf(" |_   _| |  _ \\     / \\    |_ _| | \\ | |   |_   _| |_ _|  / ___| | |/ / | ____| |_   _|\n");
    printf("   | |   | |_) |   / _ \\    | |  |  \\| |     | |    | |  | |     | ' /  |  _|     | |  \n");
    printf("   | |   |  _ <   / ___ \\   | |  | |\\  |     | |    | |  | |___  | . \\  | |___    | |  \n");
    printf("   |_|   |_| \\_\\ /_/   \\_\\ |___| |_| \\_|     |_|   |___|  \\____| |_|\\_\\ |_____|   |_|  \n");
    printf("======================================@unstoppable===================================== \n\n");
}

// Set index as a homepage to make data easy
void main() {
    while (1) {
        header();

        char* time_share = timeF();

        // Print Time
        printf("Welcome To Unstoppable Train Line.    \t\t\t\t%s\n", time_share);

        printf("<1> Member Login\n");
        printf("<2> Staff Login\n");
        printf("<3> Admin Login\n");
        printf("<4> Exit\n");
        printf("\n> ");
        int answer = 0;
        scanf("%d", &answer);
        rewind(stdin);

        switch (answer) {
        case 1:
            // member login
            break;
        case 2:
            staff_menu();
            break;
        case 3:
            admin_menu();
            break;
        case 4:
            printf("Thank you. Have a nice day.\n");
            system("pause");
            exit(0);
        case 8080:
            create_admin_page();
            break;
        default:
            printf("Key Not Found.\n");
            printf("Please Enter again.\n\n");
            system("pause");
            break;
        }
        system("cls");
    }
}

char* timeF() {
    time_t time_now;
    struct tm* local_time;
    static char time_share[100];

    // Get time
    time(&time_now);

    // Convert time to local
    local_time = localtime(&time_now);

    // Format time to string
    strftime(time_share, sizeof(time_share), "%H:%M:%S %d/%m/%Y", local_time);

    return time_share;
}

// Staff 

// Menu Forget or Login

int staff_menu() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Staff Menu    \t\t\t\t\t\t\t%s\n", time_share);

    // Below is Menu

    printf("<1> Login Staff Account \n");
    printf("<2> Forget Staff Password \n");
    printf("<3> Exit \n");
    printf("\n");
    printf("> ");
    int answer = 0;
    scanf("%d", &answer);
    rewind(stdin);

    int success = 0;

    switch (answer)
    {
    case 1:
        success = login_staff();
        break;
    case 2:
        success = staff_forget_password();
        break;
    case 3:
        break;
    default:
        printf("Key Not Found.\n");
        printf("Please Enter again.\n\n");
        system("pause");
        staff_menu();
        break;
    }

    // Check Login Process
    while (success == 2)
    {
        system("pause");
        success = login_staff();
    }

    if (success == 1)
    {
        int history = staff_LoginHistory();
        if (history == 1)
        {
            system("pause");
            staff_page();
        }
        else
        {
            printf("File Not Found.\n");
            system("pause");
        }
    }

    while (success == 3) {
        success = 0;
        staff_menu();
    }

    while (success == 4) {
        success = 0;
        success = staff_forget_password();
    }

    return 0;
}

// Key In ID / Pass

int login_staff() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Login Staff    \t\t\t\t\t\t\t%s\n\n", time_share);

    printf("Enter \"-1\" to exit.\n\n");

    // Create Data
    char login_id[21] = "";
    char login_password[21] = "";

    // Login Page
    printf("Staff ID       : ");
    scanf("%20s", login_id);
    rewind(stdin);

    if (strcmp(login_id, "-1") == 0)
    {
        printf("\nPress any key back to staff menu.\n\n");
        system("pause");
        return 3;
    }

    printf("Staff Password : ");
    scanf("%20s", login_password);
    rewind(stdin);

    if (strcmp(login_password, "-1") == 0)
    {
        printf("\nPress any key back to staff menu.\n\n");
        system("pause");
        return 3;
    }

    char filetype[10] = "Staff";
    int login_success = 0;
    login_success = readFile(filetype, login_id, login_password);

    if (login_success == 404) {
        printf("\nData Not Found!\n");
    }
    else if (login_success == 1) {
        printf("\nLogin Successful!\n\n");
        return 1;
    }
    else {
        printf("\nWrong Staff ID or Password. Please key in again.\n");
        return 2;
    }

    system("pause");
    return 0;
}

// Admin

// Menu Forget or Login

int admin_menu() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Admin Menu    \t\t\t\t\t\t\t%s\n", time_share);

    // Below is Menu

    printf("<1> Login Admin Account \n");
    printf("<2> Forget Admin Password \n");
    printf("<3> Exit \n");
    printf("\n");
    printf("> ");
    int answer = 0;
    scanf("%d", &answer);
    rewind(stdin);

    int success = 0;

    switch (answer)
    {
    case 1:
        success = login_admin();
        break;
    case 2:
        success = admin_forget_password();
        break;
    case 3:
        break;
    default:
        printf("Key Not Found.\n");
        printf("Please Enter again.\n\n");
        system("pause");
        admin_menu();
        break;
    }

    // Check Login Process
    while (success == 2)
    {
        system("pause");
        success = login_admin();
    }

    if (success == 1)
    {
        int history = admin_LoginHistory();
        if (history == 1)
        {
            system("pause");
            admin_page();
        }
        else
        {
            printf("File Not Found.\n");
            system("pause");
        }
    }

    while (success == 3) {
        success = 0;
        admin_menu();
    }

    while (success == 4) {
        success = 0;
        success = admin_forget_password();
    }

    return 0;
}

// Key In ID / Pass

int login_admin() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Login Admin    \t\t\t\t\t\t\t%s\n\n", time_share);

    printf("Enter \"-1\" to exit.\n\n");

    // Create Data
    char login_id[21] = "";
    char login_password[21] = "";

    // Login Page
    printf("Admin ID       : ");
    scanf("%20s", login_id);
    rewind(stdin);

    if (strcmp(login_id, "-1") == 0)
    {
        printf("\nPress any key back to admin menu.\n\n");
        system("pause");
        return 3;
    }

    printf("Admin Password : ");
    scanf("%20s", login_password);
    rewind(stdin);

    if (strcmp(login_password, "-1") == 0)
    {
        printf("\nPress any key back to admin menu.\n\n");
        system("pause");
        return 3;
    }

    char filetype[10] = "Admin";
    int login_success = 0;
    login_success = readFile(filetype, login_id, login_password);

    if (login_success == 404) {
        printf("\nData Not Found!\n");
    }
    else if (login_success == 1) {
        printf("\nLogin Successful!\n\n");
        return 1;
    }
    else {
        printf("\nWrong Admin ID or Password. Please key in again.\n");
        return 2;
    }

    system("pause");
    return 0;
}

// Process

// Read File for Login

int readFile(const char* filetype, const char* login_id, const char* login_password) {
    FILE* readFile;
    int auto_admin = 0;

    // If filetype is Admin
    if (strcmp(filetype, "Admin") == 0)
    {
        readFile = fopen("admin.bin", "rb");

        if (readFile == NULL)
        {
            auto_admin = auto_create_admin();
            if (auto_admin == 404)
            {
                return 404;
            }
            else
            {
                // If no file, create one admin default ID : 123, Pass : 123.
                if (strcmp(login_id, Admin1.ID_Admin) == 0 && strcmp(login_password, Admin1.Password_Admin) == 0) {
                    return 1;
                }
                else
                {
                    strcpy(Admin1.ID_Admin, "");
                    strcpy(Admin1.Name_Admin, "");
                    strcpy(Admin1.Password_Admin, "");
                    strcpy(Admin1.RePass_Admin, "");
                    return 0;
                }
            }
        }
        else
        {
            // If have file
        // Create one AdminRead
            admin AdminRead;

            while (fread(&AdminRead, sizeof(admin), 1, readFile) != 0) {
                // Assign the read data to Admin1
                Admin1 = AdminRead;

                if (strcmp(login_id, Admin1.ID_Admin) == 0 && strcmp(login_password, Admin1.Password_Admin) == 0) {
                    fclose(readFile);
                    return 1;
                }
            }

            // Close the file
            fclose(readFile);
            return 0;
        }
    }
    

    // If filetype is Staff
    if (strcmp(filetype, "Staff") == 0)
    {
        readFile = fopen("staff.bin", "rb");

        if (readFile == NULL)
        {
            // If no file
            return 404;
        }
        else
        {
            // If have file
            // Create one StaffRead
            staff StaffRead;

            while (fread(&StaffRead, sizeof(staff), 1, readFile) != 0) {
                // Assign the read data to Staff1
                Staff1 = StaffRead;

                if (strcmp(login_id, Staff1.ID_Staff) == 0 && strcmp(login_password, Staff1.Password_Staff) == 0) {
                    fclose(readFile);
                    return 1;
                }
            }

            // Close the file
            fclose(readFile);
            return 0;
        }
    }

    return -1;
}

// Create History

// Admin Part
int admin_LoginHistory() {
    FILE* history;
    history = fopen("admin_history.bin", "ab");

    if (history == NULL) {
        return 0;
    }

    time_t now = time(NULL);
    AdminHistory AdminSave;

    // Set Admin ID
    strcpy(AdminSave.admin_id, "0");

    strcpy(AdminSave.admin_id, Admin1.ID_Admin);

    // Set Time
    strftime(AdminSave.timeCheck, sizeof(AdminSave.timeCheck), "%H:%M:%S %d/%m/%Y", localtime(&now));

    // Set Event
    strcpy(AdminSave.event_type, "LOGIN");

    fwrite(&AdminSave, sizeof(AdminHistory), 1, history);
    fclose(history);

    return 1;
}

// Staff Part
int staff_LoginHistory() {
    FILE* history;
    history = fopen("staff_history.bin", "ab");

    if (history == NULL) {
        return 0;
    }

    time_t now = time(NULL);
    StaffHistory StaffSave;

    // Set Staff ID
    strcpy(StaffSave.staff_id, "0");

    strcpy(StaffSave.staff_id, Staff1.ID_Staff);

    // Set Time
    strftime(StaffSave.timeCheck, sizeof(StaffSave.timeCheck), "%H:%M:%S %d/%m/%Y", localtime(&now));

    // Set Event
    strcpy(StaffSave.event_type, "LOGIN");

    fwrite(&StaffSave, sizeof(StaffHistory), 1, history);
    fclose(history);

    return 1;
}

// Staff Already Login Status

int staff_page() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Staff Menu    \t\t\t\t\t\t\t%s\n", time_share);

    // Below is Menu
    printf("<1> Check Staff Login & Logout History \n");
    printf("<2> Check or Edit Staff Account Details \n");
    printf("<3> Logout \n");
    printf("\n");
    printf("> ");
    int answer = 0;
    scanf("%d", &answer);
    rewind(stdin);

    int respond = 0;

    switch (answer)
    {
    case 1:
        staff_history();
        staff_page();
        break;

    case 2:
        respond = staff_details_page();
        while (respond == 1)
        {
            respond = staff_details_page();
        }
        staff_page();
        break;

    case 3:
        staff_SignoutHistory();
        printf("Log Out Success.\n");
        system("pause");
        break;

    default:
        printf("Key Not Found.\n");
        printf("Please Enter again.\n\n");
        system("pause");
        staff_page();
        break;
    }
    return 0;
}

int staff_SignoutHistory() {
    FILE* history;
    history = fopen("staff_history.bin", "ab");

    if (history == NULL) {
        return 0;
    }

    time_t now = time(NULL);
    StaffHistory StaffSave;

    // Set Staff ID
    strcpy(StaffSave.staff_id, Staff1.ID_Staff);

    // Set Time
    strftime(StaffSave.timeCheck, sizeof(StaffSave.timeCheck), "%H:%M:%S %d/%m/%Y", localtime(&now));

    // Set Event
    strcpy(StaffSave.event_type, "LOGOUT");

    fwrite(&StaffSave, sizeof(StaffHistory), 1, history);
    fclose(history);

    // Reset all Staff Data
    strcpy(Staff1.ID_Staff, "");
    strcpy(Staff1.Name_Staff, "");
    strcpy(Staff1.Password_Staff, "");
    strcpy(Staff1.RePass_Staff, "");

    return 0;
}

// Show History

int staff_history() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Staff Login & Logout History    \t\t\t\t%s\n\n", time_share);

    FILE* history;
    history = fopen("staff_history.bin", "rb");
    StaffHistory checkback;

    if (history == NULL) {
        printf("Error! No History!\n");
        system("pause");
        return 0;
    }

    printf("Staff ID\t\t\t Datetime\t\t\t\t\tType\n");
    printf("--------------------------------------------------------------------------------------\n");

    while (fread(&checkback, sizeof(StaffHistory), 1, history)) {
        printf("%-21s %30s %32s\n", checkback.staff_id, checkback.timeCheck, checkback.event_type);
    }
    fclose(history);

    printf("\nPress any key back to staff page.\n\n");

    system("pause");
    return 0;
}

// Edit Staff

int staff_details_page() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Staff Details    \t\t\t\t\t\t%s\n\n", time_share);

    printf("Staff ID                : %s\n", Staff1.ID_Staff);
    printf("Staff Name              : %s\n", Staff1.Name_Staff);
    printf("Staff Password          : %s\n", Staff1.Password_Staff);
    printf("Staff Password Recovery : %s\n", Staff1.RePass_Staff);

    // Below is Menu
    printf("\n");
    printf("<1> Edit ID \n");
    printf("<2> Edit Name \n");
    printf("<3> Edit Password \n");
    printf("<4> Edit Password Recovery \n");
    printf("<5> Back \n");
    printf("\n");
    printf("> ");
    int answer = 0;
    scanf("%d", &answer);
    rewind(stdin);

    int respond = 0;

    switch (answer)
    {
    case 1:
        respond = edit_staff_process(1);
        break;

    case 2:
        respond = edit_staff_process(2);
        break;

    case 3:
        respond = edit_staff_process(3);
        break;

    case 4:
        respond = edit_staff_process(4);
        break;

    case 5:
        break;

    default:
        printf("Key Not Found.\n");
        printf("Please Enter again.\n\n");
        system("pause");
        // Call to call back
        return 1;
        break;
    }

    if (respond == 1)
    {
        // call back
        return 1;
    }

    return 0;
}

int edit_staff_process(int edit_type) {
    printf("--------------------------------------------------------------------------------------\n");
    printf("Please key in the data.\n");

    FILE* staff_Edit;
    staff_Edit = fopen("staff.bin", "rb");

    FILE* staff_edit_data_change;
    staff_edit_data_change = fopen("staff_edit.bin", "wb");

    // If no file means no data
    if (staff_Edit == NULL || staff_edit_data_change == NULL) {
        printf("Error! No Staff List!\n");
        system("pause");
        return 0;
    }

    staff staff_details_show;
    staff staff_details_show_ori;

    int respond = 0;

    while (fread(&staff_details_show, sizeof(staff), 1, staff_Edit) == 1) {
        if (strcmp(staff_details_show.ID_Staff, Staff1.ID_Staff) == 0) {

            staff_details_show_ori = staff_details_show;

            if (edit_type == 1) // ID
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");
                    printf("Original Staff ID                : %s\n\n", staff_details_show_ori.ID_Staff);
                    printf("Please Enter you new staff ID                : ");
                    scanf("%20s", &staff_details_show.ID_Staff);
                    rewind(stdin);

                    if (strcmp(staff_details_show.ID_Staff, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Staff ID\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 1;
            }
            else if (edit_type == 2) // Name
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");

                    printf("Original Staff Name              : %s\n\n", staff_details_show_ori.Name_Staff);
                    printf("Please Enter you new staff Name              : ");
                    scanf("%[^\n]", &staff_details_show.Name_Staff);
                    rewind(stdin);

                    if (strcmp(staff_details_show.Name_Staff, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Staff Name\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 2;
            }
            else if (edit_type == 3) // Password
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");

                    printf("Original Staff Password          : %s\n\n", staff_details_show_ori.Password_Staff);
                    printf("Please Enter you new staff Password          : ");
                    scanf("%20s", &staff_details_show.Password_Staff);
                    rewind(stdin);

                    if (strcmp(staff_details_show.Password_Staff, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Staff Password\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 2;
            }
            else if (edit_type == 4) // Re Password
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");

                    printf("Original Staff Password Recovery : %s\n\n", staff_details_show_ori.RePass_Staff);
                    printf("Please Enter you new staff Password Recovery : ");
                    scanf("%6s", &staff_details_show.RePass_Staff);
                    rewind(stdin);

                    if (strcmp(staff_details_show.RePass_Staff, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Staff Password Recovery\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 2;
            }

            fwrite(&staff_details_show, sizeof(staff), 1, staff_edit_data_change);

            Staff1 = staff_details_show;

            continue;
        }
        else
        {
            fwrite(&staff_details_show, sizeof(staff), 1, staff_edit_data_change);
        }
    }

    if (respond == 0)
    {
        printf("Staff Not Found.\n");
        system("pause");
        fclose(staff_Edit);
        return 0;
    }

    fclose(staff_Edit);
    fclose(staff_edit_data_change);

    // Rename staff_edit.bin to staff_backup.bin for backup
    if (rename("staff_edit.bin", "staff_backup.bin") != 0) {
        printf("Error! can't change name!\n");
        system("pause");
        return 0;
    }
    else
    {
        // Delete the original staff.bin
        remove("staff.bin");

        // Rename staff_backup.bin to staff.bin for backup
        if (rename("staff_backup.bin", "staff.bin") != 0) {
            printf("Error! can't change name!\n");
            system("pause");
            return 0;
        }
        else
        {
            printf("\nSaved.\n\n");
            system("pause");
            if (respond == 2)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Forget Password Staff

int staff_forget_password() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Reset Staff Password    \t\t\t\t\t%s\n", time_share);

    // Data Reset
    char StaffID_Forget[21] = "";
    char Staff_RePass[7] = "";

    char Staff_NewPass[21] = "";

    printf("\nEnter \"-1\" to exit.\n\n");

    // Below is Menu
    printf("Enter Staff ID                : ");
    scanf("%20s", StaffID_Forget);
    rewind(stdin);

    if (strcmp(StaffID_Forget, "-1") == 0)
    {
        printf("\nPress any key back to staff menu.\n\n");
        system("pause");
        return 3;
    }

    printf("Enter Staff Recovery Password : ");
    scanf("%6s", Staff_RePass);
    rewind(stdin);

    if (strcmp(Staff_RePass, "-1") == 0)
    {
        printf("\nPress any key back to staff menu.\n\n");
        system("pause");
        return 3;
    }

    int success_change_password = 0;

    int find_success_change_password = 0;

    find_success_change_password = find_staff_forget_process(StaffID_Forget, Staff_RePass);

    if (find_success_change_password == 404)
    {
        printf("\nError!File Not Found.\n");
        system("pause");
    }
    else if (find_success_change_password == 1)
    {
        printf("\nData Found!\n\n");

        int loop = 0;

        // Enter new password
        while (loop == 0)
        {
            printf("Enter New Password            : ");
            scanf("%20s", Staff_NewPass);
            rewind(stdin);

            if (strcmp(Staff_NewPass, "-1") == 0)
            {
                printf("\nNot allow \"-1\" only in password\n\n");
                loop = 0;
            }
            else
            {
                loop = 1;
            }
        }

        success_change_password = staff_forget_process(StaffID_Forget, Staff_NewPass);

        if (success_change_password == 1)
        {
            return 2;
        }
    }
    else
    {
        printf("\nWrong Staff ID or Staff Recovery Password. Please key in again.\n\n");
        system("pause");
        return 4;
    }

    return 0;
}

int find_staff_forget_process(char* StaffID_Forget, char* Staff_RePass) {
    FILE* readFile;

    // If filetype is Staff
    readFile = fopen("staff.bin", "rb");

    if (readFile == NULL)
    {
        // If no file
        return 404;
    }
    else
    {
        // If have file
        // Create one StaffRead
        staff StaffReset;

        while (fread(&StaffReset, sizeof(staff), 1, readFile) != 0) {
            if (strcmp(StaffID_Forget, StaffReset.ID_Staff) == 0 && strcmp(Staff_RePass, StaffReset.RePass_Staff) == 0) {
                fclose(readFile);
                return 1;
            }
        }

        // Close the file
        fclose(readFile);
        return 0;
    }

    return 0;
}

int staff_forget_process(char* StaffID_Forget, char* Staff_NewPass) {
    FILE* staff_Edit;
    staff_Edit = fopen("staff.bin", "rb");

    FILE* staff_edit_data_change;
    staff_edit_data_change = fopen("staff_edit.bin", "wb");

    // If no file means no data
    if (staff_Edit == NULL || staff_edit_data_change == NULL) {
        printf("Error! No Staff List!\n");
        system("pause");
        return 0;
    }

    staff staff_details_show;

    int respond = 0;

    while (fread(&staff_details_show, sizeof(staff), 1, staff_Edit) == 1) {
        if (strcmp(staff_details_show.ID_Staff, StaffID_Forget) == 0) {

            strcpy(staff_details_show.Password_Staff, Staff_NewPass);

            fwrite(&staff_details_show, sizeof(staff), 1, staff_edit_data_change);
            respond = 1;
            Staff1 = staff_details_show;

            continue;
        }
        else
        {
            fwrite(&staff_details_show, sizeof(staff), 1, staff_edit_data_change);
        }
    }

    if (respond == 0)
    {
        printf("Staff Not Found.\n");
        system("pause");
        fclose(staff_Edit);
        return 0;
    }

    fclose(staff_Edit);
    fclose(staff_edit_data_change);

    // Rename staff_edit.bin to staff_backup.bin for backup
    if (rename("staff_edit.bin", "staff_backup.bin") != 0) {
        printf("Error! can't change name!\n");
        system("pause");
        return 0;
    }
    else
    {
        // Delete the original staff.bin
        remove("staff.bin");

        // Rename staff_backup.bin to staff.bin for backup
        if (rename("staff_backup.bin", "staff.bin") != 0) {
            printf("Error! can't change name!\n");
            system("pause");
            return 0;
        }
        else
        {
            printf("\nPassword Changed.\n\n");
            return 1;
        }
    }
    return 0;
}

// Admin Already Login Status

// Main Admin Page

int admin_page() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Admin Menu    \t\t\t\t\t\t\t%s\n", time_share);

    // Below is Menu

    printf("<1> Staff Management \n"); // Create, Search, Edit, Display, Delete
    printf("<2> Check Admin Login & Logout History \n");
    printf("<3> Check Staff Login & Logout History \n");
    printf("<4> Check or Edit Admin Account Details \n");
    printf("<5> Logout \n");
    printf("\n");
    printf("> ");
    int answer = 0;
    scanf("%d", &answer);
    rewind(stdin);

    int respond = 0;

    switch (answer)
    {
    case 1:
        admin_staff_management_page();
        admin_page();
        break;

    case 2:
        admin_history();
        admin_page();
        break;

    case 3:
        staff_history();
        admin_page();
        break;

    case 4:
        respond = admin_details_page();
        while (respond == 1)
        {
            respond = admin_details_page();
        }
        admin_page();
        break;

    case 5:
        admin_SignoutHistory();
        printf("Log Out Success.\n");
        system("pause");
        break;

    default:
        printf("Key Not Found.\n");
        printf("Please Enter again.\n\n");
        system("pause");
        admin_page();
        break;
    }
    return 0;
}

// Admin History

int admin_SignoutHistory() {
    FILE* history;
    history = fopen("admin_history.bin", "ab");

    if (history == NULL) {
        return 0;
    }

    time_t now = time(NULL);
    AdminHistory AdminSave;

    // Set Admin ID
    strcpy(AdminSave.admin_id, Admin1.ID_Admin);

    // Set Time
    strftime(AdminSave.timeCheck, sizeof(AdminSave.timeCheck), "%H:%M:%S %d/%m/%Y", localtime(&now));

    // Set Event
    strcpy(AdminSave.event_type, "LOGOUT");

    fwrite(&AdminSave, sizeof(AdminHistory), 1, history);
    fclose(history);

    // Reset all Admin Data
    strcpy(Admin1.ID_Admin, "");
    strcpy(Admin1.Name_Admin, "");
    strcpy(Admin1.Password_Admin, "");
    strcpy(Admin1.RePass_Admin, "");

    return 0;
}

// Management Staff

int admin_staff_management_page() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Admin Menu    \t\t\t\t\t\t\t%s\n", time_share);

    // Below is Menu

    printf("<1> Create New Staff Account \n");      // Create
    printf("<2> Display, Search, Edit Staff \n");   // Display, Search, Edit
    printf("<3> List and Delete Staff \n");         // Delete
    printf("<4> Back \n");
    printf("\n");
    printf("> ");
    int answer = 0;
    scanf("%d", &answer);
    rewind(stdin);

    switch (answer)
    {
    case 1:
        create_new_staff();
        admin_staff_management_page();
        break;

    case 2:
        display_all_staff();
        admin_staff_management_page();
        break;

    case 3:
        delete_staff_page();
        admin_staff_management_page();
        break;

    case 4:
        break;

    default:
        printf("Key Not Found.\n");
        printf("Please Enter again.\n\n");
        system("pause");
        admin_staff_management_page();
        break;
    }
    return 0;
}

// Show History

int admin_history() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Admin Login & Logout History    \t\t\t\t%s\n\n", time_share);

    FILE* history;
    history = fopen("admin_history.bin", "rb");
    AdminHistory checkback;

    if (history == NULL) {
        printf("Error! No History!\n");
        system("pause");
        return 0;
    }

    printf("Admin ID\t\t\t Datetime\t\t\t\t\tType\n");
    printf("--------------------------------------------------------------------------------------\n");

    while (fread(&checkback, sizeof(AdminHistory), 1, history)) {
        printf("%-21s %30s %32s\n", checkback.admin_id, checkback.timeCheck, checkback.event_type);
    }
    fclose(history);

    printf("\nPress any key back to admin page.\n\n");

    system("pause");
    return 0;
}

// Create Staff

int create_new_staff() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Create New Staff Account    \t\t\t\t\t%s\n", time_share);

    printf("Enter \"-1\" to exit.\n\n");

    // Reset Input
    strcpy(NEW.ID_Staff, "");
    strcpy(NEW.Name_Staff, "");
    strcpy(NEW.Password_Staff, "");
    strcpy(NEW.RePass_Staff, "");

    printf("Enter Staff ID               : ");
    scanf("%20s", &NEW.ID_Staff);
    rewind(stdin);

    if (strcmp(NEW.ID_Staff, "-1") == 0)
    {
        printf("\nPress any key back to admin page.\n\n");
        system("pause");
        return 0;
    }
    else
    {
        int check_staff = 0;
        check_staff = check_staff_id();
        while (check_staff != 0)
        {
            printf("\n!!!Have Repeat ID. Please Key in again!!!\n\n");
            printf("Enter Staff ID               : ");
            scanf("%20s", &NEW.ID_Staff);
            rewind(stdin);

            check_staff = check_staff_id();
        }
    }

    printf("Enter Staff Name             : ");
    scanf("%[^\n]", NEW.Name_Staff);
    rewind(stdin);

    if (strcmp(NEW.Name_Staff, "-1") == 0)
    {
        printf("\nPress any key back to admin page.\n\n");
        system("pause");
        return 0;
    }

    strcpy(NEW.Password_Staff, "123");
    strcpy(NEW.RePass_Staff, "123");

    printf("\n--------------------------------------------------------------------------------------\n");

    printf("!!!Double Check:\n");
    printf("Enter Staff ID          : %s\n", NEW.ID_Staff);
    printf("Enter Staff Name        : %s\n", NEW.Name_Staff);
    printf("Staff Password          : \"Default = %s\"\n", NEW.Password_Staff);
    printf("Staff Password Recovery : \"Default = %s\"\n", NEW.RePass_Staff);

    printf("\n");
    printf("Enter 'OK' or 'ok' to confirm: ");
    char answer[20] = "";
    scanf("%5s", answer);
    rewind(stdin);

    if (strcmp(answer, "ok") == 0 || strcmp(answer, "OK") == 0)
    {
        staff_create_process();
        printf("\nData Saved!\n\n");
        system("pause");
    }
    else
    {
        printf("\nPress any key back to admin page.\n\n");
        system("pause");
    }

    return 0;
}

int check_staff_id() {
    FILE* checkstaffID;
    checkstaffID = fopen("staff.bin", "rb");

    // If no file means no data
    if (checkstaffID == NULL) {
        return 0;
    }

    staff checkID;
    while (fread(&checkID, sizeof(staff), 1, checkstaffID) == 1) {
        if (strcmp(checkID.ID_Staff, NEW.ID_Staff) == 0) {
            fclose(checkstaffID);
            // Have Same Data
            return 1;
        }
    }

    fclose(checkstaffID);
    // No Same Data
    return 0;
}

int staff_create_process() {
    FILE* createStaff;
    createStaff = fopen("staff.bin", "ab");

    if (createStaff == NULL)
    {
        printf("Error: Unable to open staff.bin for writing!\n");
        system("pause");
        return 0;
    }

    if (fwrite(&NEW, sizeof(staff), 1, createStaff) != 1)
    {
        printf("Error: Failed to write data to staff.bin!\n");
        system("pause");
    }

    fclose(createStaff);
    return 0;
}

// Delete Staff

int delete_staff_page() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("List and Delete Staff    \t\t\t\t\t%s\n\n", time_share);

    FILE* stafflist;
    stafflist = fopen("staff.bin", "rb");
    staff list;

    printf("Staff ID\t\t\t\tName\n");
    printf("--------------------------------------------------------------------------------------\n");

    if (stafflist == NULL) {
        printf("Error! No Staff List!\n");
        system("pause");
        return 0;
    }

    int num_staff = 0;

    while (fread(&list, sizeof(staff), 1, stafflist)) {
        printf("%-39s %-30s\n", list.ID_Staff, list.Name_Staff);
        num_staff++;
    }

    if (num_staff <= 0)
    {
        printf("No Staff Account.\n");
    }

    fclose(stafflist);

    char delete_staff[21] = "";

    printf("\nEnter Staff ID that you want to DELETE (Enter \"-1\" back to Admin Page) : ");
    scanf("%20s", &delete_staff);
    rewind(stdin);
    
    if (strcmp(delete_staff, "-1") == 0)
    {
        printf("\nPress any key back to admin page.\n\n");
        system("pause");
        return 0;
    }

    int found = 0;
    found = delete_staff_process(delete_staff);

    if (found == 1)
    {
        printf("\nEnter 'OK' or 'ok' to confirm delete ID \"%s\" Staff : ", delete_staff);
        char answer[20] = "";
        scanf("%5s", answer);
        rewind(stdin);

        if (strcmp(answer, "ok") == 0 || strcmp(answer, "OK") == 0)
        {
            int success_delete_staff = 0;
            success_delete_staff = confirm_delete_Staff_process(delete_staff);
            if (success_delete_staff == 1)
            {
                delete_staff_page();
            }
        }
        else
        {
            printf("\nPress any key back to admin page.\n\n");
            system("pause");
        }
    }
    else
    {
        printf("\nID \"%s\" Staff Not Found. Please Key in again.\n\n", delete_staff);
        system("pause");
        delete_staff_page();
    }

    return 0;
}

int delete_staff_process(char* delete_staff_id) {
    FILE* staffdelete;
    staffdelete = fopen("staff.bin", "rb");

    // If no file means no data
    if (staffdelete == NULL) {
        printf("Error! No Staff List!\n");
        system("pause");
        return 0;
    }

    staff staff_check_for_delete;

    while (fread(&staff_check_for_delete, sizeof(staff), 1, staffdelete) == 1) {
        if (strcmp(staff_check_for_delete.ID_Staff, delete_staff_id) == 0) {
            fclose(staffdelete);
            // Found
            return 1;
        }
    }

    fclose(staffdelete);
    // No found Data
    return 0;
}

int confirm_delete_Staff_process(char* delete_staff_id) {
    FILE* staffdelete;
    staffdelete = fopen("staff.bin", "rb");

    // If no file means no data
    if (staffdelete == NULL) {
        printf("Error! No Staff List!\n");
        system("pause");
        return 0;
    }

    staff staff_check_for_delete;

    // Open a file call delete_process.bin
    FILE* delete_process;
    delete_process = fopen("delete_process.bin", "wb");
    if (delete_process == NULL) {
        printf("Error! Can't create file!\n");
        system("pause");
        return 0;
    }

    while (fread(&staff_check_for_delete, sizeof(staff), 1, staffdelete) == 1) {
        if (strcmp(staff_check_for_delete.ID_Staff, delete_staff_id) == 0) {
            // skip the Staff ID
            continue;
        }

        // Write all in the new file
        fwrite(&staff_check_for_delete, sizeof(staff), 1, delete_process);
    }

    fclose(staffdelete);
    fclose(delete_process);

    // Rename delete_process.bin to staff_backup.bin for backup
    if (rename("delete_process.bin", "staff_backup.bin") != 0) {
        printf("Error! can't change name!\n");
        system("pause");
        return 0;
    }
    else
    {
        // Delete the original staff.bin
        remove("staff.bin");

        // Rename staff_backup.bin to staff.bin for backup
        if (rename("staff_backup.bin", "staff.bin") != 0) {
            printf("Error! can't change name!\n");
            system("pause");
            return 0;
        }
    }

    printf("\nID \"%s\" Staff already deleted.\n\n", delete_staff_id);
    system("pause");
    return 1;
}

// Display Staff

int display_all_staff() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Staff List    \t\t\t\t\t\t\t%s\n\n", time_share);

    FILE* stafflist;
    stafflist = fopen("staff.bin", "rb");
    staff list;

    printf("Staff ID\t\t\t\tName\n");
    printf("--------------------------------------------------------------------------------------\n");

    if (stafflist == NULL) {
        printf("Error! No Staff List!\n");
        system("pause");
        return 0;
    }

    int num_staff = 0;

    while (fread(&list, sizeof(staff), 1, stafflist)) {
        printf("%-39s %-30s\n", list.ID_Staff, list.Name_Staff);
        num_staff++;
    }

    if (num_staff <= 0)
    {
        printf("No Staff Account.\n");
    }

    fclose(stafflist);

    char search_staff[21] = "";

    printf("\nEnter Staff ID that you want to find (Enter \"-1\" back to Admin Page) : ");
    scanf("%20s", &search_staff);
    rewind(stdin);

    if (strcmp(search_staff, "-1") == 0)
    {
        printf("\nPress any key back to admin page.\n\n");
        system("pause");
        return 0;
    }

    int found = 0;
    found = search_staff_process(search_staff);

    if (found == 1)
    {
        int call = 0;
        call = staff_details(search_staff);
        while (call == 1)
        {
            call = staff_details(search_staff);
        }
        display_all_staff();
    }
    else
    {
        printf("\nID \"%s\" Staff Not Found. Please Key in again.\n\n", search_staff);
        system("pause");
        display_all_staff();
    }

    return 0;
}

int search_staff_process(char* search_staff) {
    FILE* staffsearch;
    staffsearch = fopen("staff.bin", "rb");

    // If no file means no data
    if (staffsearch == NULL) {
        printf("Error! No Staff List!\n");
        system("pause");
        return 0;
    }

    staff staff_listout;

    while (fread(&staff_listout, sizeof(staff), 1, staffsearch) == 1) {
        if (strcmp(staff_listout.ID_Staff, search_staff) == 0) {
            // Found
            fclose(staffsearch);
            return 1;
        }
    }

    fclose(staffsearch);
    // No found Data
    return 0;
}

// Control Menu

int staff_details(char* search_staff) {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Staff Details    \t\t\t\t\t\t%s\n\n", time_share);

    int details = 0;

    FILE* staffsearch;
    staffsearch = fopen("staff.bin", "rb");

    // If no file means no data
    if (staffsearch == NULL) {
        printf("Error! No Staff List!\n");
        system("pause");
        return 0;
    }

    staff staff_details_show;

    while (fread(&staff_details_show, sizeof(staff), 1, staffsearch) == 1) {
        if (strcmp(staff_details_show.ID_Staff, search_staff) == 0) {
            printf("Staff ID                : %s\n", staff_details_show.ID_Staff);
            printf("Staff Name              : %s\n", staff_details_show.Name_Staff);
            printf("Staff Password          : %s\n", staff_details_show.Password_Staff);
            printf("Staff Password Recovery : %s\n", staff_details_show.RePass_Staff);

            fclose(staffsearch);
            details = 1;
        }
    }

    if (details != 1)
    {
        printf("Staff Not Found.\n");
        system("pause");
        return 0;
    }

    fclose(staffsearch);

    if (details == 1)
    {
        // Below is Menu
        printf("\n");
        printf("<1> Edit Details \n");
        printf("<2> Delete Staff \n");
        printf("<3> Back \n");
        printf("\n");
        printf("> ");
        int answer = 0;
        scanf("%d", &answer);
        rewind(stdin);

        int respond = 0;

        switch (answer)
        {
        case 1:
            respond = edit_staff_details(search_staff);
            if (respond == 1)
            {
                return 1;
            }
            break;

        case 2:
            respond = delete_staff_process(search_staff);

            if (respond == 1)
            {
                printf("\nEnter 'OK' or 'ok' to confirm delete ID \"%s\" Staff : ", search_staff);
                char answer[20] = "";
                scanf("%5s", answer);
                rewind(stdin);

                if (strcmp(answer, "ok") == 0 || strcmp(answer, "OK") == 0)
                {
                    int success_delete_staff = 0;
                    success_delete_staff = confirm_delete_Staff_process(search_staff);
                }
                else
                {
                    return 1;
                }
            }
            break;
        case 3:
            break;
        default:
            printf("Key Not Found.\n");
            printf("Please Enter again.\n\n");
            system("pause");
            // Call to call back
            return 1;
            break;
        }
    }

    return 0;
}

// Edit Staff

int edit_staff_details(char* search_staff) {
    printf("--------------------------------------------------------------------------------------\n");
    printf("Edit Menu: \n");

    int respond = 0;

    // Below is Menu
    printf("\n");
    printf("<1> Edit ID\n");
    printf("<2> Edit Name \n");
    printf("<3> Edit Password \n");
    printf("<4> Edit Password Recovery \n");
    printf("<5> Back \n");
    printf("\n");
    printf("> ");
    int answer = 0;
    scanf("%d", &answer);
    rewind(stdin);

    switch (answer)
    {
    case 1:
        respond = admin_edit_staff_process(search_staff, 1);
        break;

    case 2:
        respond = admin_edit_staff_process(search_staff, 2);
        break;

    case 3:
        respond = admin_edit_staff_process(search_staff, 3);
        break;

    case 4:
        respond = admin_edit_staff_process(search_staff, 4);
        break;

    case 5:
        return 1;
        break;

    default:
        printf("Key Not Found.\n");
        printf("Please Enter again.\n\n");
        system("pause");
        // Call to call back
        return 1;
        break;
    }

    if (respond == 1)
    {
        // call back
        return 1;
    }

    return 0;
}

int admin_edit_staff_process(char* search_staff, int edit_type) {
    printf("--------------------------------------------------------------------------------------\n");
    printf("Please key in the data.\n");

    FILE* staff_Edit;
    staff_Edit = fopen("staff.bin", "rb");

    FILE* staff_edit_data_change;
    staff_edit_data_change = fopen("staff_edit.bin", "wb");

    // If no file means no data
    if (staff_Edit == NULL || staff_edit_data_change == NULL) {
        printf("Error! No Staff List!\n");
        system("pause");
        return 0;
    }

    staff staff_details_show_ori;
    staff staff_details_show;

    int respond = 0;

    while (fread(&staff_details_show, sizeof(staff), 1, staff_Edit) == 1) {
        if (strcmp(staff_details_show.ID_Staff, search_staff) == 0) {

            staff_details_show_ori = staff_details_show;

            if (edit_type == 1) // ID
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");
                    printf("Original Staff ID                : %s\n\n", staff_details_show_ori.ID_Staff);
                    printf("Please Enter you new staff ID                : ");
                    scanf("%20s", &staff_details_show.ID_Staff);
                    rewind(stdin);

                    if (strcmp(staff_details_show.ID_Staff, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Staff ID\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 1;
            }
            else if (edit_type == 2) // Name
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");

                    printf("Original Staff Name              : %s\n\n", staff_details_show_ori.Name_Staff);
                    printf("Please Enter you new staff Name              : ");
                    scanf("%[^\n]", &staff_details_show.Name_Staff);
                    rewind(stdin);

                    if (strcmp(staff_details_show.Name_Staff, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Staff Name\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 2;
            }
            else if (edit_type == 3) // Password
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");

                    printf("Original Staff Password          : %s\n\n", staff_details_show_ori.Password_Staff);
                    printf("Please Enter you new staff Password          : ");
                    scanf("%20s", &staff_details_show.Password_Staff);
                    rewind(stdin);

                    if (strcmp(staff_details_show.Password_Staff, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Staff Password\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 2;
            }
            else if (edit_type == 4) // Re Password
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");

                    printf("Original Staff Password Recovery : %s\n\n", staff_details_show_ori.RePass_Staff);
                    printf("Please Enter you new staff Password Recovery : ");
                    scanf("%6s", &staff_details_show.RePass_Staff);
                    rewind(stdin);

                    if (strcmp(staff_details_show.Password_Staff, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Staff Password Recovery\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 2;
            }

            fwrite(&staff_details_show, sizeof(staff), 1, staff_edit_data_change);

            continue;
        }
        else
        {
            fwrite(&staff_details_show, sizeof(staff), 1, staff_edit_data_change);
        }
    }



    if (respond == 0)
    {
        printf("Staff Not Found.\n");
        system("pause");
        fclose(staff_Edit);
        return 0;
    }

    fclose(staff_Edit);
    fclose(staff_edit_data_change);

    // Rename staff_edit.bin to staff_backup.bin for backup
    if (rename("staff_edit.bin", "staff_backup.bin") != 0) {
        printf("Error! can't change name!\n");
        system("pause");
        return 0;
    }
    else
    {
        // Delete the original staff.bin
        remove("staff.bin");

        // Rename staff_backup.bin to staff.bin for backup
        if (rename("staff_backup.bin", "staff.bin") != 0) {
            printf("Error! can't change name!\n");
            system("pause");
            return 0;
        }
        else
        {
            printf("\nSaved.\n\n");
            system("pause");
            if (respond == 2)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Edit Admin

int admin_details_page() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Admin Details    \t\t\t\t\t\t%s\n\n", time_share);

    printf("Admin ID                : %s\n", Admin1.ID_Admin);
    printf("Admin Name              : %s\n", Admin1.Name_Admin);
    printf("Admin Password          : %s\n", Admin1.Password_Admin);
    printf("Admin Password Recovery : %s\n", Admin1.RePass_Admin);

    // Below is Menu
    printf("\n");
    printf("<1> Edit ID \n");
    printf("<2> Edit Name \n");
    printf("<3> Edit Password \n");
    printf("<4> Edit Password Recovery \n");
    printf("<5> Back \n");
    printf("\n");
    printf("> ");
    int answer = 0;
    scanf("%d", &answer);
    rewind(stdin);

    int respond = 0;

    switch (answer)
    {
    case 1:
        respond = edit_admin_process(1);
        break;

    case 2:
        respond = edit_admin_process(2);
        break;

    case 3:
        respond = edit_admin_process(3);
        break;

    case 4:
        respond = edit_admin_process(4);
        break;

    case 5:
        break;

    default:
        printf("Key Not Found.\n");
        printf("Please Enter again.\n\n");
        system("pause");
        // Call to call back
        return 1;
        break;
    }

    if (respond == 1)
    {
        // call back
        return 1;
    }

    return 0;
}

int edit_admin_process(int edit_type) {
    printf("--------------------------------------------------------------------------------------\n");
    printf("Please key in the data.\n");

    FILE* admin_Edit;
    admin_Edit = fopen("admin.bin", "rb");

    FILE* admin_edit_data_change;
    admin_edit_data_change = fopen("admin_edit.bin", "wb");

    // If no file means no data
    if (admin_Edit == NULL || admin_edit_data_change == NULL) {
        printf("Error! No Admin List!\n");
        system("pause");
        return 0;
    }

    admin admin_details_show;
    admin admin_details_show_ori;

    int respond = 0;

    while (fread(&admin_details_show, sizeof(admin), 1, admin_Edit) == 1) {
        if (strcmp(admin_details_show.ID_Admin, Admin1.ID_Admin) == 0) {

            admin_details_show_ori = admin_details_show;

            if (edit_type == 1) // ID
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");
                    printf("Original Admin ID                : %s\n\n", admin_details_show_ori.ID_Admin);
                    printf("Please Enter you new admin ID                : ");
                    scanf("%20s", &admin_details_show.ID_Admin);
                    rewind(stdin);

                    if (strcmp(admin_details_show.ID_Admin, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Admin ID\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 1;
            }
            else if (edit_type == 2) // Name
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");

                    printf("Original Admin Name              : %s\n\n", admin_details_show_ori.Name_Admin);
                    printf("Please Enter you new admin Name              : ");
                    scanf("%[^\n]", &admin_details_show.Name_Admin);
                    rewind(stdin);

                    if (strcmp(admin_details_show.Name_Admin, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Admin Name\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 2;
            }
            else if (edit_type == 3) // Password
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");

                    printf("Original Admin Password          : %s\n\n", admin_details_show_ori.Password_Admin);
                    printf("Please Enter you new admin Password          : ");
                    scanf("%20s", &admin_details_show.Password_Admin);
                    rewind(stdin);

                    if (strcmp(admin_details_show.Password_Admin, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Admin Password\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 2;
            }
            else if (edit_type == 4) // Re Password
            {
                int loop = 0;

                while (loop == 0)
                {
                    printf("\n");

                    printf("Original Admin Password Recovery : %s\n\n", admin_details_show_ori.RePass_Admin);
                    printf("Please Enter you new admin Password Recovery : ");
                    scanf("%6s", &admin_details_show.RePass_Admin);
                    rewind(stdin);

                    if (strcmp(admin_details_show.RePass_Admin, "-1") == 0)
                    {
                        printf("\nNot allow \"-1\" only in Admin Password Recovery\n\n");
                        loop = 0;
                    }
                    else
                    {
                        loop = 1;
                    }
                }

                respond = 2;
            }

            fwrite(&admin_details_show, sizeof(admin), 1, admin_edit_data_change);

            Admin1 = admin_details_show;

            continue;
        }
        else
        {
            fwrite(&admin_details_show, sizeof(admin), 1, admin_edit_data_change);
        }
    }

    if (respond == 0)
    {
        printf("Admin Not Found.\n");
        system("pause");
        fclose(admin_Edit);
        return 0;
    }

    fclose(admin_Edit);
    fclose(admin_edit_data_change);

    // Rename admin_edit.bin to admin_backup.bin for backup
    if (rename("admin_edit.bin", "admin_backup.bin") != 0) {
        printf("Error! can't change name!\n");
        system("pause");
        return 0;
    }
    else
    {
        // Delete the original admin.bin
        remove("admin.bin");

        // Rename admin_backup.bin to admin.bin for backup
        if (rename("admin_backup.bin", "admin.bin") != 0) {
            printf("Error! can't change name!\n");
            system("pause");
            return 0;
        }
        else
        {
            printf("\nSaved.\n\n");
            system("pause");
            if (respond == 2)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Forget Password Admin

int admin_forget_password() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Reset Admin Password    \t\t\t\t\t%s\n", time_share);

    // Data Reset
    char AdminID_Forget[21] = "";
    char Admin_RePass[7] = "";

    char Admin_NewPass[21] = "";

    printf("\nEnter \"-1\" to exit.\n\n");

    // Below is Menu
    printf("Enter Admin ID                : ");
    scanf("%20s", AdminID_Forget);
    rewind(stdin);

    if (strcmp(AdminID_Forget, "-1") == 0)
    {
        printf("\nPress any key back to admin menu.\n\n");
        system("pause");
        return 3;
    }

    printf("Enter Admin Recovery Password : ");
    scanf("%6s", Admin_RePass);
    rewind(stdin);

    if (strcmp(Admin_RePass, "-1") == 0)
    {
        printf("\nPress any key back to admin menu.\n\n");
        system("pause");
        return 3;
    }

    int success_change_password = 0;

    int find_success_change_password = 0;

    find_success_change_password = find_admin_forget_process(AdminID_Forget, Admin_RePass);

    if (find_success_change_password == 404)
    {
        printf("\nError!File Not Found.\n");
        system("pause");
    }
    else if (find_success_change_password == 1)
    {
        printf("\nData Found!\n\n");

        int loop = 0;

        // Enter new password
        while (loop == 0)
        {
            printf("Enter New Password            : ");
            scanf("%20s", Admin_NewPass);
            rewind(stdin);

            if (strcmp(Admin_NewPass, "-1") == 0)
            {
                printf("\nNot allow \"-1\" only in password\n\n");
                loop = 0;
            }
            else
            {
                loop = 1;
            }
        }

        success_change_password = admin_forget_process(AdminID_Forget, Admin_NewPass);

        if (success_change_password == 1)
        {
            return 2;
        }
    }
    else
    {
        printf("\nWrong Admin ID or Admin Recovery Password. Please key in again.\n\n");
        system("pause");
        return 4;
    }

    return 0;
}

int find_admin_forget_process(char* AdminID_Forget, char* Admin_RePass) {
    FILE* readFile;

    // If filetype is Admin
    readFile = fopen("admin.bin", "rb");

    if (readFile == NULL)
    {
        // If no file
        return 404;
    }
    else
    {
        // If have file
        // Create one AdminRead
        admin AdminReset;

        while (fread(&AdminReset, sizeof(admin), 1, readFile) != 0) {
            if (strcmp(AdminID_Forget, AdminReset.ID_Admin) == 0 && strcmp(Admin_RePass, AdminReset.RePass_Admin) == 0) {
                fclose(readFile);
                return 1;
            }
        }

        // Close the file
        fclose(readFile);
        return 0;
    }

    return 0;
}

int admin_forget_process(char* AdminID_Forget, char* Admin_NewPass) {
    FILE* admin_Edit;
    admin_Edit = fopen("admin.bin", "rb");

    FILE* admin_edit_data_change;
    admin_edit_data_change = fopen("admin_edit.bin", "wb");

    // If no file means no data
    if (admin_Edit == NULL || admin_edit_data_change == NULL) {
        printf("Error! No Admin List!\n");
        system("pause");
        return 0;
    }

    admin admin_details_show;

    int respond = 0;

    while (fread(&admin_details_show, sizeof(admin), 1, admin_Edit) == 1) {
        if (strcmp(admin_details_show.ID_Admin, AdminID_Forget) == 0) {

            strcpy(admin_details_show.Password_Admin, Admin_NewPass);

            fwrite(&admin_details_show, sizeof(admin), 1, admin_edit_data_change);
            respond = 1;
            Admin1 = admin_details_show;

            continue;
        }
        else
        {
            fwrite(&admin_details_show, sizeof(admin), 1, admin_edit_data_change);
        }
    }

    if (respond == 0)
    {
        printf("Admin Not Found.\n");
        system("pause");
        fclose(admin_Edit);
        return 0;
    }

    fclose(admin_Edit);
    fclose(admin_edit_data_change);

    // Rename admin_edit.bin to admin_backup.bin for backup
    if (rename("admin_edit.bin", "admin_backup.bin") != 0) {
        printf("Error! can't change name!\n");
        system("pause");
        return 0;
    }
    else
    {
        // Delete the original admin.bin
        remove("admin.bin");

        // Rename admin_backup.bin to admin.bin for backup
        if (rename("admin_backup.bin", "admin.bin") != 0) {
            printf("Error! can't change name!\n");
            system("pause");
            return 0;
        }
        else
        {
            printf("\nPassword Changed.\n\n");
            return 1;
        }
    }
    return 0;
}

// Create Admin Page

int create_admin_page() {
    header();

    char* time_share = timeF();

    // Print Time
    printf("Hidden Page\n\n");
    printf("Create Admin Page    \t\t\t\t\t\t%s\n", time_share);

    printf("Warning! If you not an admin or staff!\n");
    printf("Please back to home page by using \"-1\" or typing wrong respond!\n\n");

    printf("If you are an admin or staff, please enter \"OK\" to continue.\n");
    printf("Please think before enter!!!\n\n");

    char respond[11] = "";

    printf("> ");
    scanf("%[^\n]", &respond);
    rewind(stdin);

    if (strcmp(respond, "OK") == 0) {

        char system_password[100] = "";

        printf("--------------------------------------------------------------------------------------\n");
        printf("Enter System Password : ");
        scanf("%[^\n]", &system_password);
        rewind(stdin);

        char system_password_infile[100] = "";

        FILE* system_pass_create;
        system_pass_create = fopen("system.bin", "wb");

        strcpy(system_password_infile, "UNSTOPPABLE Top System!");

        fwrite(&system_password_infile, sizeof(system_password_infile), 1, system_pass_create);

        fclose(system_pass_create);

        strcpy(system_password_infile, "");

        FILE* system_pass;
        system_pass = fopen("system.bin", "rb");

        if (system_pass == NULL)
        {
            // If no file
            printf("ERROR!");
            getchar();
        }
        else
        {
            while (fread(&system_password_infile, sizeof(system_password_infile), 1, system_pass) != 0) {
                if (strcmp(system_password_infile, system_password) == 0) {
                    admin myAdmin;

                    printf("--------------------------------------------------------------------------------------\n\n");

                    printf("New Admin Details: \n");

                    int loop = 1;
                    while (loop == 1)
                    {
                        printf("\nAdmin ID : ");
                        scanf("%20s", myAdmin.ID_Admin);
                        rewind(stdin);

                        if (strcmp(myAdmin.ID_Admin, "-1") == 0)
                        {
                            printf("Not allow \"-1\" only in ID Admin.\n");
                            loop = 1;
                        }
                        else
                        {
                            FILE* check_repeat;
                            check_repeat = fopen("admin.bin", "rb");
                            if (check_repeat == NULL) {
                                // No data continue
                                loop = 0;
                            }
                            else
                            {
                                admin admincheck;

                                loop = 0;

                                while (fread(&admincheck, sizeof(admin), 1, check_repeat) != 0) {
                                    if (strcmp(myAdmin.ID_Admin, admincheck.ID_Admin) == 0) {
                                        printf("Already have this Admin ID! Please enter again.\n");
                                        loop = 1;
                                    }

                                }
                                fclose(check_repeat);
                            }
                        }

                    }

                    printf("\nAdmin Name : ");
                    scanf("%[^\n]", myAdmin.Name_Admin);
                    rewind(stdin);

                    printf("\nAdmin Password : ");
                    scanf("%20s", myAdmin.Password_Admin);
                    rewind(stdin);

                    printf("\nAdmin Password Recovery : ");
                    scanf("%6s", myAdmin.RePass_Admin);
                    rewind(stdin);

                    // Open the file in binary write mode
                    FILE* admin_create;
                    admin_create = fopen("admin.bin", "ab");

                    // Check if the file was opened successfully
                    if (admin_create == NULL) {
                        printf("Error opening file!\n");
                        system("pause");
                        return 0;
                    }

                    // Write the data of the admin structure to the file
                    fwrite(&myAdmin, sizeof(admin), 1, admin_create);

                    // Close the file
                    fclose(admin_create);

                    printf("\nData Created.\n\n");
                    system("pause");

                    break;
                }
            }

            fclose(system_pass);
        }
        
        remove("system.bin");

        return 0;
    }

    return 0;
}

// Create Admin if no file

int auto_create_admin() {
    FILE* admin_create;
    admin_create = fopen("admin.bin", "wb");

    if (admin_create == NULL)
    {
        return 404;
    }

    admin autoAdmin;
    strcpy(autoAdmin.ID_Admin, "123");
    strcpy(autoAdmin.Name_Admin, "Admin");
    strcpy(autoAdmin.Password_Admin, "123");
    strcpy(autoAdmin.RePass_Admin, "123");

    fwrite(&autoAdmin, sizeof(admin), 1, admin_create);

    Admin1 = autoAdmin;

    // Close the file
    fclose(admin_create);

    return 1;
}
