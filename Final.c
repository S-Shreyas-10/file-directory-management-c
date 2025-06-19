 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PATH_LENGTH 500

typedef struct File {
    int size;
    char creation_date[20];
    char modification_date[20];
} File;

typedef struct TreeNode {
    char name[MAX_NAME_LENGTH];
    int is_directory;
    union {
        File file_data;
    } data;
    struct TreeNode* parent;
    struct TreeNode* children;
    struct TreeNode* next_sibling;
} TreeNode;

typedef struct {
    TreeNode* root;
    TreeNode* current_directory;
} FileSystem;

FileSystem fileSystem;

void initializeFileSystem() {
    fileSystem.root = malloc(sizeof(TreeNode));
    strcpy(fileSystem.root->name, "C:\\");
    fileSystem.root->is_directory = 1;
    fileSystem.root->parent = NULL;
    fileSystem.root->children = NULL;
    fileSystem.root->next_sibling = NULL;
    fileSystem.current_directory = fileSystem.root;
}

TreeNode* createNode(char name[], int is_directory) {
    TreeNode* newNode = malloc(sizeof(TreeNode));
    strcpy(newNode->name, name);
    newNode->is_directory = is_directory;
    newNode->parent = NULL;
    newNode->children = NULL;
    newNode->next_sibling = NULL;
    return newNode;
}

void addNodeToDirectory(TreeNode* directory, TreeNode* node) {
    if (directory->children == NULL) {
        directory->children = node;
    } else {
        TreeNode* currentChild = directory->children;
        while (currentChild->next_sibling != NULL) {
            currentChild = currentChild->next_sibling;
        }
        currentChild->next_sibling = node;
    }
    node->parent = directory;
}

void listDirectories(TreeNode* directory) {
    TreeNode* currentChild = directory->children;
    while (currentChild != NULL) {
        if (currentChild->is_directory) {
            printf("- %s\n", currentChild->name);
        }
        currentChild = currentChild->next_sibling;
    }
}

TreeNode* findDirectoryByName(TreeNode* startDirectory, const char* name) {
    TreeNode* currentChild = startDirectory->children;
    while (currentChild != NULL) {
        if (currentChild->is_directory && strcmp(currentChild->name, name) == 0) {
            return currentChild;
        }
        currentChild = currentChild->next_sibling;
    }
    return NULL;
}

void createDirectory(char name[]) {
    TreeNode* newDirectory = createNode(name, 1);
    addNodeToDirectory(fileSystem.current_directory, newDirectory);
    printf("Directory '%s' created successfully.\n", name);
}

void createFile(char name[], int size, char creation_date[], char modification_date[]) {
    TreeNode* newFileNode = createNode(name, 0);
    newFileNode->data.file_data.size = size;
    strcpy(newFileNode->data.file_data.creation_date, creation_date);
    strcpy(newFileNode->data.file_data.modification_date, modification_date);
    addNodeToDirectory(fileSystem.current_directory, newFileNode);
    printf("File '%s' created successfully.\n", name);
}

void printAbsolutePath(TreeNode* node) {
    if (node->parent != NULL) {
        printAbsolutePath(node->parent);
        printf("\\%s", node->name);
    } else {
        printf("\\%s", node->name);
    }
}

void printRelativePath(TreeNode* current_directory) {
    if (current_directory == NULL || strcmp(current_directory->name, "C:\\") == 0) {
        printf("Relative Path: .\n");
        return;
    }

    if (current_directory->parent != NULL) {
        printf("Relative Path: \\%s\\%s\n", current_directory->parent->name, current_directory->name);
    } else {
        printf("Relative Path: \\%s\n", current_directory->name);
    }
}


void changeDirectory() {
    printf("Available directories:\n");
    listDirectories(fileSystem.current_directory);

    char targetDirectoryName[MAX_NAME_LENGTH];
    printf("Enter target directory name (or '..' to go up): ");
    fgets(targetDirectoryName, sizeof(targetDirectoryName), stdin);
    targetDirectoryName[strcspn(targetDirectoryName, "\n")] = '\0';

    if (strcmp(targetDirectoryName, "..") == 0) {
        if (fileSystem.current_directory->parent != NULL) {
            fileSystem.current_directory = fileSystem.current_directory->parent;
            printf("Moved up to the parent directory.\n");
        } else {
            printf("Already at the root directory.\n");
        }
    } else {
        TreeNode* targetDirectory = findDirectoryByName(fileSystem.current_directory, targetDirectoryName);

        if (targetDirectory != NULL) {
            fileSystem.current_directory = targetDirectory;
            printf("Changed to directory: %s\n", targetDirectoryName);
        } else {
            printf("Directory not found.\n");
        }
    }
}

void displayFileSystem(TreeNode* node, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    if (node->is_directory) {
        printf("[D] %s\n", node->name);
    } else {
        printf("[F] %s (Size: %d, Created: %s, Modified: %s)\n", 
               node->name, node->data.file_data.size,
               node->data.file_data.creation_date,
               node->data.file_data.modification_date);
    }

    TreeNode* currentChild = node->children;
    while (currentChild != NULL) {
        displayFileSystem(currentChild, depth + 1);
        currentChild = currentChild->next_sibling;
    }
}

void printOptions() {
    printf("\nOptions:\n");
    printf("1. Create Directory\n");
    printf("2. Create File\n");
    printf("3. Change Directory\n");
    printf("4. Display File System Hierarchy\n");
    printf("5. Print Absolute Path\n");
    printf("6. Print Relative Path\n");
    printf("7. Exit\n");
}

int main() {
    initializeFileSystem();

    fileSystem.current_directory = fileSystem.root;

    char command[50];
    while (1) {
        printOptions();
        printf("Enter option (1-7): ");
        fgets(command, sizeof(command), stdin);

        if (strncmp(command, "1", 1) == 0) {
            char newDirectoryName[MAX_NAME_LENGTH];

            printf("Enter directory name: ");
            fgets(newDirectoryName, sizeof(newDirectoryName), stdin);
            newDirectoryName[strcspn(newDirectoryName, "\n")] = '\0';
            createDirectory(newDirectoryName);
        } else if (strncmp(command, "2", 1) == 0) {
            char newFileName[MAX_NAME_LENGTH];
            int size;
            char creation_date[20];
            char modification_date[20];

            printf("Enter file name: ");
            fgets(newFileName, sizeof(newFileName), stdin);
            newFileName[strcspn(newFileName, "\n")] = '\0';
            printf("Enter file size: ");
            scanf("%d", &size);
            getchar();

            printf("Enter creation date: ");
            fgets(creation_date, sizeof(creation_date), stdin);
            creation_date[strcspn(creation_date, "\n")] = '\0';

            printf("Enter modification date: ");
            fgets(modification_date, sizeof(modification_date), stdin);
            modification_date[strcspn(modification_date, "\n")] = '\0';

            createFile(newFileName, size, creation_date, modification_date);
        } else if (strncmp(command, "3", 1) == 0) {
            changeDirectory();
        } else if (strncmp(command, "4", 1) == 0) {
            printf("\nFile System Hierarchy:\n");
            displayFileSystem(fileSystem.root, 0);
        } else if (strncmp(command, "5", 1) == 0) {
            printf("Absolute Path: ");
            printAbsolutePath(fileSystem.current_directory);
            printf("\n");
        } else if (strncmp(command, "6", 1) == 0) {
            printRelativePath(fileSystem.current_directory);
        } else if (strncmp(command, "7", 1) == 0) {
            break;
        } else {
            printf("Invalid option.\n");
        }
    }

    return 0;
}
