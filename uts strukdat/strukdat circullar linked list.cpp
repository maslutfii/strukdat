#include <stdio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

void tambahAwal(node **head);
void tambahAkhir(node **head);
void tambahData(node **head);
void hapusAwal(node **head);
void hapusDataTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void hitungJumlahData(node *head);
void jumlahkanData(node *head);
void tranverse(node *head);

//========================================================

int main() {
    node *head = NULL;
    char pilih;

    do {
        system("cls");
        printf("masukkan pilihan\n");
        printf("1. tambah data di awal\n");
        printf("2. tambah data di akhir\n");
        printf("3. tambah data di tengah list\n");
        printf("4. hapus data di awal\n");
        printf("5. hapus data di tengah\n");
        printf("6. hapus data di akhir\n");
        printf("7. cari data\n");
        printf("8. cetak isi list\n");
        printf("9. hitung jumlah data\n");
        printf("0. jumlahkan semua data\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf(" %c", &pilih); 

        switch (pilih) {
            case '1': tambahAwal(&head); break;
            case '2': tambahAkhir(&head); break;
            case '3': tambahData(&head); break;
            case '4': hapusAwal(&head); break;
            case '5': hapusDataTengah(&head); break;
            case '6': hapusAkhir(&head); break;
            case '7': cariData(head); break;
            case '8': tranverse(head); system("pause"); break;
            case '9': hitungJumlahData(head); system("pause"); break;
            case '0': jumlahkanData(head); system("pause"); break;
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    printf("masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        if (*head == NULL) {
            pNew->next = pNew;  
        } else {
            node *pLast = *head;
            while (pLast->next != *head) {
                pLast = pLast->next; 
            }
            pNew->next = *head;
            pLast->next = pNew;
        }
        *head = pNew; 
    } else {
        printf("Alokasi memori gagal");
        system("pause");
    }
}

//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pLast;

    system("cls");
    printf("masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        if (*head == NULL) {
            pNew->next = pNew; // Jika list kosong, buat circular
            *head = pNew;
        } else {
            pLast = *head;
            while (pLast->next != *head) {
                pLast = pLast->next; // Mencari node terakhir
            }
            pLast->next = pNew; // Menghubungkan node terakhir ke node baru
            pNew->next = *head; // Buat circular
        }
    } else {
        printf("Alokasi memori gagal");
        system("pause");
    }
}

//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai : ");
    scanf("%d", &pos);
    printf("\nbilangan : ");
    scanf("%d", &bil);

    pCur = *head;
    if (pCur == NULL) {
        printf("\nList kosong.\n");
        system("pause");
        return;
    }

    do {
        if (pCur->data == pos) {
            break;
        }
        pCur = pCur->next;
    } while (pCur != *head);

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL || pNew == NULL) {
        printf("\nNode tidak ditemukan atau alokasi memori gagal");
        system("pause");
        return;
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
    }
}

//========================================================

void hapusAwal(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
    } else if ((*head)->next == *head) {  // Hanya ada satu node
        free(*head);
        *head = NULL;
        printf("Data di awal telah dihapus.\n");
    } else {
        node *pTemp = *head;
        node *pLast = *head;

        while (pLast->next != *head) {  // Mencari node terakhir
            pLast = pLast->next;
        }

        *head = (*head)->next;  // Update head
        pLast->next = *head;    // Update pointer terakhir
        free(pTemp);
        printf("Data di awal telah dihapus.\n");
    }
    system("pause");
}

//========================================================

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
    } else if ((*head)->next == *head) {  // Hanya ada satu node
        free(*head);
        *head = NULL;
        printf("Data di akhir telah dihapus.\n");
    } else {
        node *pCur = *head;
        node *pPrev = NULL;

        while (pCur->next != *head) {  // Mencari node terakhir
            pPrev = pCur;
            pCur = pCur->next;
        }

        pPrev->next = *head;  // Update pointer sebelum terakhir
        free(pCur);
        printf("Data di akhir telah dihapus.\n");
    }
    system("pause");
}

//========================================================

void hapusDataTengah(node **head) {
    int bil;
    node *pCur, *pPrev;

    system("cls");
    tranverse(*head);
    printf("\nmasukkan data yang ingin dihapus : ");
    scanf("%d", &bil);

    pCur = *head;
    pPrev = NULL;

    if (pCur == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        system("pause");
        return;
    }

    do {
        if (pCur->data == bil) {
            break;
        }
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head);

    if (pCur == *head && pCur->data == bil) { // Jika head yang ingin dihapus
        hapusAwal(head);
    } else if (pCur != NULL) { // Jika ditemukan node yang ingin dihapus
        pPrev->next = pCur->next;
        free(pCur);
        printf("\nData telah dihapus.");
    } else {
        printf("\nData tidak ditemukan");
    }
    system("pause");
}

//========================================================

void cariData(node *head) {
    int bil;
    node *pCur = head;
    int found = 0;

    system("cls");
    printf("masukkan data yang dicari : ");
    scanf("%d", &bil);

    if (pCur == NULL) {
        printf("List kosong.\n");
        return;
    }

    do {
        if (pCur->data == bil) {
            printf("Data %d ditemukan.\n", bil);
            found = 1;
            break;
        }
        pCur = pCur->next;
    } while (pCur != head);

    if (!found) {
        printf("Data tidak ditemukan.\n");
    }
    system("pause");
}

//========================================================

void hitungJumlahData(node *head) {
    int count = 0;
    node *pCur = head;

    if (pCur == NULL) {
        printf("List kosong.\n");
        return;
    }

    do {
        count++;
        pCur = pCur->next;
    } while (pCur != head);

    printf("Jumlah data dalam list: %d\n", count);
}

//========================================================

void jumlahkanData(node *head) {
    int sum = 0;
    node *pCur = head;

    if (pCur == NULL) {
        printf("List kosong.\n");
        return;
    }

    do {
        sum += pCur->data;
        pCur = pCur->next;
    } while (pCur != head);

    printf("Jumlah total semua data dalam list: %d\n", sum);
}

//========================================================

void tranverse(node *head) {
    node *pWalker = head;

    system("cls");
    if (pWalker == NULL) {
        printf("List kosong.\n");
        return;
    }

    do {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    } while (pWalker != head);
    printf("(kembali ke %d)\n", head->data);
}

