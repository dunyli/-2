// Лаба 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Лабораторная №2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Header.h"

// Функция для добавления нового клиента
void add_client(struct Store* store) {
    struct Client new_client;
    printf("Введите имя клиента: ");
    scanf("%s", new_client.name);
    printf("Введите телефон клиента: ");
    scanf("%s", new_client.phone);
    printf("Введите адрес клиента: ");
    scanf("%s", new_client.address);
    // Добавление нового клиента в массив клиентов
    store->clients[store->num_clients] = new_client;
    store->num_clients++;
    printf("Клиент добавлен!\n");
}

// Функция для добавления новой категории
void add_category(struct Store* store) {
    struct Category new_category;
    printf("Введите название категории: ");
    scanf("%s", new_category.name);
    // Добавление новой категории в массив категорий
    store->categories[store->num_categories] = new_category;
    store->num_categories++;
    printf("Категория добавлена!\n");
}

// Функция для добавления нового поставщика
void add_supplier(struct Store* store) {
    struct Supplier new_supplier;
    printf("Введите название поставщика: ");
    scanf("%s", new_supplier.name);
    printf("Введите адрес поставщика: ");
    scanf("%s", new_supplier.address);
    printf("Введите телефон поставщика: ");
    scanf("%s", new_supplier.phone);
    // Добавление нового поставщика в массив поставщиков
    store->suppliers[store->num_supplier] = new_supplier;
    store->num_supplier++;
    printf("Поставщик добавлен!\n");
}

// Функция для добавления нового товара
void add_product(struct Store* store) {
    struct Product new_product;
    int catogory_id, supplier_id;
    printf("Введите ID категории: ");
    scanf("%d", &catogory_id);
    if (catogory_id > 0 && catogory_id <= store->num_categories) {
        printf("Введите ID поставщика: ");
        scanf("%d", &supplier_id);
        if (supplier_id > 0 && supplier_id <= store->num_supplier) {
            printf("Введите название товара: ");
            scanf("%s", new_product.name);
            printf("Введите цену товара: ");
            scanf("%d", &new_product.price);
            printf("Введите количество товара: ");
            scanf("%d", &new_product.kolvo);
            // Добавление нового товара в массив товаров
            store->products[store->num_products] = new_product;
            store->num_products++;
            printf("Товар добавлен!\n");
        }
        else printf("Неверный ID поставщика!");
    }
    else printf("Неверный ID категории!\n");
}

// Функция для создания нового заказа
void create_order(struct OrderHistory* history) {
    struct Order new_order;
    int client_id, product_id, kolvo;
    printf("Введите ID клиента: ");
    scanf("%d", &client_id);
    new_order.client_id = client_id;
    new_order.num_products = 0;
    new_order.total_price = 0;
    printf("Введите ID товара (или 0 для завершения): ");
    scanf("%d", &product_id);
    while (product_id != 0) {
        if (product_id > 0 && product_id <= history->num_products) {
            printf("Введите количество товара: ");
            scanf("%d", &kolvo);
            if (kolvo > 0 && kolvo <= history->products[product_id - 1].kolvo) {
                new_order.products[new_order.num_products] = history->products[product_id - 1];
                new_order.products[new_order.num_products].kolvo = kolvo;
                new_order.total_price += new_order.products[new_order.num_products].price * kolvo;
                new_order.num_products++;
                history->products[product_id - 1].kolvo -= kolvo;
            }
            else {
                printf("Неверное количество товара!\n");
            }
        }
        else {
            printf("Неверный ID товара!\n");
        }
        printf("Введите ID товара (или 0 для завершения): ");
        scanf("%d", &product_id);
    }

    // Добавление нового заказа в массив заказов
    history->orders[history->orderCount] = new_order;
    history->orderCount++;
    printf("Заказ создан!\n");
}

// Функция для вывода списка клиентов
void list_clients(struct Store* store) {
    printf("Список клиентов:\n");
    for (int i = 0; i < store->num_clients; i++) {
        printf("ID: %d\n", i + 1);
        printf("Имя: %s\n", store->clients[i].name);
        printf("Телефон: %s\n", store->clients[i].phone);
        printf("Адрес: %s\n", store->clients[i].address);
        printf("\n");
    }
}

// Функция для вывода списка категорий
void list_category(struct Store* store) {
    printf("Список категорий:\n");
    for (int i = 0; i < store->num_categories; i++) {
        printf("ID: %d\n", i + 1);
        printf("Название категории: %s\n", store->categories[i].name);
        printf("\n");
    }
}

// Функция для вывода списка поставщиков
void list_supplier(struct Store* store) {
    printf("Список поставщиков:\n");
    for (int i = 0; i < store->num_supplier; i++) {
        printf("ID: %d\n", i + 1);
        printf("Название поставщика: %s\n", store->suppliers[i].name);
        printf("Адрес поставщика: %s\n", store->suppliers[i].address);
        printf("Телефон поставщика: %s\n", store->suppliers[i].phone);
        printf("\n");
    }
}

// Функция для вывода списка заказов
void list_orders(struct OrderHistory* history) {
    printf("Список заказов:\n");
    for (int i = 0; i < history->orderCount; i++) {
        printf("Номер заказа: %d\n", i + 1);
        printf("ID клиента: %d\n", history->orders[i].client_id);
        printf("Товары:\n");
        for (int j = 0; j < history->orders[i].num_products; j++) {
            printf("%d. %s (количество: %d)\n", j + 1, history->orders[i].products[j].name, history->orders[i].products[j].kolvo);
        }
        printf("Общая стоимость: %d\n", history->orders[i].total_price);
        printf("\n");
    }
}

// Функция для вывода списка товаров
void list_products(struct Store* store) {
    printf("Список товаров:\n");
    for (int i = 0; i < store->num_products; i++) {
        printf("ID: %d\n", i + 1);
        printf("Категория: %s\n", store->categories[i].name);
        printf("Поставщик: %s\n", store->suppliers[i].name);
        printf("Название: %s\n", store->products[i].name);
        printf("Цена: %d\n", store->products[i].price);
        printf("Количество: %d\n", store->products[i].kolvo);
        printf("\n");
    }
}

// Функция для вывода меню
void outmenu() {
    printf("\nЗоомагазин Собачий Патруль\n");
    printf("1. Добавить клиента\n");
    printf("2. Добавить категорию\n");
    printf("3. Добавить поставщика\n");
    printf("4. Добавить товар\n");
    printf("5. Создать заказ\n");
    printf("6. Вывести список клиентов\n");
    printf("7. Вывести список категорий\n");
    printf("8. Вывести список поставщиков\n");
    printf("9. Вывести список товаров\n");
    printf("10. Вывести список заказов\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}

int main()
{
    setlocale(LC_ALL, "RUS");
    system("chcp 1251");
    struct Store store;
    store.num_clients = 0;
    store.num_categories = 0;
    store.num_supplier = 0;
    store.num_products = 0;
    struct OrderHistory history;
    history.num_products = 0;
    int choice;
    do {
        outmenu();
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            add_client(&store);
            break;
        case 2:
            add_category(&store);
            break;
        case 3:
            add_supplier(&store);
            break;
        case 4:
            add_product(&store);
            break;
        case 5:
            create_order(&history);
            break;
        case 6:
            list_clients(&store);
            break;
        case 7:
            list_category(&store);
            break;
        case 8:
            list_supplier(&store);
            break;
        case 9:
            list_products(&store);
            break;
        case 10:
            list_orders(&history);
            break;
        case 0:
            printf("Выход\n");
            break;
        default:
            printf("Неверный выбор!\n");
        }
    } while (choice != 0);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
