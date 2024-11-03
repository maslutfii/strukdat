#include <stdio.h>
#include <conio.h>
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

int main()
{
  node *head;
  char pilih;

  head = NULL;
  do{
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
     scanf("%c", &pilih);
     if (pilih == '1')
     		tambahAwal(&head);
     else if (pilih == '2')
     		tambahAkhir(&head);
     else if (pilih == '3')
			tambahData(&head);
     else if (pilih == '4')
			hapusAwal(&head);
     else if (pilih == '5')
			hapusDataTengah(&head);
     else if (pilih == '6')
			hapusAkhir(&head);
     else if (pilih == '7')
     		cariData(head);
     else if (pilih == '8'){
     		tranverse(head);
         getch();
     }
     else if (pilih == '9'){
     		hitungJumlahData(head);
         getch();
     }
     else if (pilih == '0'){
     		jumlahkanData(head);
         getch();
     }
  } while (pilih != 'q');
  
  return 0;
}

//========================================================

void tambahAwal(node **head){
  int bil;
  node *pNew;

  system("cls");
  printf("masukkan bilangan : ");
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
  	  pNew->data = bil;
      pNew->next = *head;
      *head = pNew;
  }
  else{
      printf("Alokasi memori gagal");
      getch();
  }
}

//========================================================

void tambahAkhir(node **head){
  int bil;
  node *pNew, *pLast;

  system("cls");
  printf("masukkan bilangan : ");
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
  	  pNew->data = bil;
      pNew->next = NULL;

      if (*head == NULL){
          *head = pNew;
      } else {
          pLast = *head;
          while (pLast->next != NULL){
              pLast = pLast->next;
          }
          pLast->next = pNew;
      }
  }
  else{
      printf("Alokasi memori gagal");
      getch();
  }
}

//========================================================

void tambahData(node **head){
  int pos, bil;
  node *pNew, *pCur;

  system("cls");
  tranverse(*head);
  printf("\nposisi penyisipan setelah data bernilai : ");
  scanf("%d", &pos);
  printf("\nbilangan : ");
  scanf("%d", &bil);

  pCur = *head;
  while (pCur != NULL && pCur->data != pos) {
    pCur = pCur->next;
  }

  pNew = (node *)malloc(sizeof(node));

  if (pCur == NULL){
     printf("\nnode tidak ditemukan");
     getch();
  }
  else if (pNew == NULL){
     printf("\nalokasi memori gagal");
     getch();
  }
  else{
     pNew->data = bil;
     pNew->next = pCur->next;
     pCur->next = pNew;
  }
}

//========================================================

void hapusAwal(node **head){
    node *pTemp;
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
    } else {
        pTemp = *head;
        *head = (*head)->next;
        free(pTemp);
        printf("Data di awal telah dihapus.\n");
    }
    getch();
}

//========================================================

void hapusAkhir(node **head){
    node *pCur, *pPrev;
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
    } else if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        printf("Data di akhir telah dihapus.\n");
    } else {
        pCur = *head;
        while (pCur->next != NULL) {
            pPrev = pCur;
            pCur = pCur->next;
        }
        free(pCur);
        pPrev->next = NULL;
        printf("Data di akhir telah dihapus.\n");
    }
    getch();
}

//========================================================

void hapusDataTengah(node **head){
    int bil;
    node *pCur, *pPrev;

    system("cls");
    tranverse(*head);
    printf("\nmasukkan data yang ingin dihapus : ");
    scanf("%d", &bil);

    pCur = *head;
    pPrev = NULL;
    while (pCur != NULL && pCur->data != bil) {
        pPrev = pCur;
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("\nData tidak ditemukan");
    } else {
        if (pPrev == NULL) {
            *head = pCur->next;
        } else {
            pPrev->next = pCur->next;
        }
        free(pCur);
        printf("\nData telah dihapus.");
    }
    getch();
}

//========================================================

void cariData(node *head){
    int bil;
    node *pCur = head;
    int found = 0;

    system("cls");
    printf("masukkan data yang dicari : ");
    scanf("%d", &bil);

    while (pCur != NULL) {
        if (pCur->data == bil) {
            printf("Data %d ditemukan.\n", bil);
            found = 1;
            break;
        }
        pCur = pCur->next;
    }

    if (!found) {
        printf("Data tidak ditemukan.\n");
    }

    getch();
}

//========================================================

void hitungJumlahData(node *head){
    int count = 0;
    node *pCur = head;

    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }

    printf("Jumlah data dalam list: %d\n", count);
}

//========================================================

void jumlahkanData(node *head){
    int sum = 0;
    node *pCur = head;

    while (pCur != NULL) {
        sum += pCur->data;
        pCur = pCur->next;
    }

    printf("Jumlah total semua data dalam list: %d\n", sum);
}

//========================================================

void tranverse(node *head){
    node *pWalker = head;

    system("cls");
    if (pWalker == NULL) {
        printf("List kosong.\n");
        return;
    }

    while (pWalker != NULL){
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    }
    printf("NULL\n");
}