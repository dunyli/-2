// Лаба 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Лабораторная №2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <malloc.h>
#include <Windows.h>
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
    store->clients = (Client*)realloc(store->clients, (store->num_clients + 1) * sizeof(struct Client));
    strcpy(store->clients[store->num_clients].name, new_client.name);
    strcpy(store->clients[store->num_clients].phone, new_client.phone);
    strcpy(store->clients[store->num_clients].address, new_client.address);
    store->num_clients++;
    printf("Клиент добавлен!\n");
}

// Функция для добавления новой категории
void add_category(struct Store* store) {
    struct Category new_category;
    printf("Введите название категории: ");
    scanf("%s", new_category.name);
    // Добавление новой категории в массив категорий
    store->categories = (Category*)realloc(store->categories, (store->num_categories + 1) * sizeof(struct Category));
    strcpy(store->categories[store->num_categories].name, new_category.name);
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
    store->suppliers = (Supplier*)realloc(store->suppliers, (store->num_suppliers + 1) * sizeof(struct Supplier));
    store->suppliers[store->num_suppliers] = new_supplier;
    store->num_suppliers++;
    printf("Поставщик добавлен!\n");
}

// Функция для добавления нового товара
void add_product(struct Store* store, struct Storehouse* storehouse) {
    if (store->num_products==0) storehouse->products = (Product*)malloc((store->num_products + 1) * sizeof(struct Product));
    struct Product new_product;
    int category_id, supplier_id;
    printf("Введите ID категории: ");
    scanf("%d", &category_id);
    if (category_id > 0 && category_id <= store->num_categories) {
        printf("Введите ID поставщика: ");
        scanf("%d", &supplier_id);
        if (supplier_id > 0 && supplier_id <= store->num_suppliers) {
            printf("Введите название товара: ");
            scanf("%s", new_product.name);
            printf("Введите цену товара: ");
            scanf("%d", &new_product.price);
            printf("Введите количество товара: ");
            scanf("%d", &new_product.count);
            new_product.category_id = category_id  - 1;
            new_product.supplier_id = supplier_id - 1;
            // Добавление нового товара в массив товаров
            storehouse->products = (Product*)realloc(storehouse->products, (store->num_products + 1) * sizeof(struct Product));
            storehouse->products[store->num_products] = new_product;
            store->num_products++;
            printf("Товар добавлен!\n");
        }
        else printf("Неверный ID поставщика!");
    }
    else printf("Неверный ID категории!\n");
}

// Функция для создания нового заказа
void create_order(struct Store* store, struct OrderHistory* history, struct Storehouse* storehouse) {
    int client_id, product_id, volume;
    struct Order new_order;
    if (history->orderCount == 0) history->orders = (Order*)malloc((history->orderCount + 1) * sizeof(struct Order));
    do {
        printf("Введите ID клиента: ");
        scanf("%d", &client_id);
    } while (client_id < 0 || client_id > store->num_clients);
    new_order.client_id = client_id;
    new_order.num_products = 0;
    new_order.total_price = 0;
    printf("Введите ID товара (или 0 для завершения): ");
    scanf("%d", &product_id);
    while (product_id != 0) {
        if (product_id > 0 && product_id <= store->num_products) {
            printf("Введите количество товара: ");
            scanf("%d", &volume);
            if (volume > 0 && volume <= storehouse->products[product_id - 1].count) {
                if (new_order.num_products==0) new_order.products = (Product*)malloc((new_order.num_products + 1) * sizeof(struct Product));
                new_order.products = (Product*)realloc(new_order.products, (new_order.num_products + 1) * sizeof(struct Product));
                new_order.products[new_order.num_products] = storehouse->products[product_id - 1];
                new_order.products[new_order.num_products].count = volume;
                new_order.total_price += new_order.products[new_order.num_products].price * volume;
                new_order.status_order = 0;
                new_order.num_products++;
                storehouse->products[product_id - 1].count -= volume;
            }
            else {
                printf("Неверное количество товара!\n");
            }
        }
        else {
            printf("Неверный ID товара!\n");
        }
        printf("Введите ID нового товара (или 0 для завершения): ");
        scanf("%d", &product_id);
    }
    // Добавление нового заказа в массив заказов
    history->orders = (Order*)realloc(history->orders, (history->orderCount + 1) * sizeof(struct Order));
    history->orders[history->orderCount].products = (Product*)malloc((new_order.num_products + 1) * sizeof(struct Product));
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
    for (int i = 0; i < store->num_suppliers; i++) {
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
            printf("%d. %s (количество: %d)\n", j + 1, history->orders[i].products[j].name, history->orders[i].products[j].count);
        }
        printf("Общая стоимость: %d\n", history->orders[i].total_price);
        printf("\n");
    }
}

// Функция для вывода списка товаров
void list_products(struct Store* store, struct Storehouse* storehouse) {
    printf("Список товаров:\n");
    for (int i = 0; i < store->num_products; i++) {
        printf("ID: %d\n", i + 1);
        printf("Категория: %s\n", store->categories[storehouse->products[i].category_id].name);
        printf("Поставщик: %s\n", store->suppliers[storehouse->products[i].supplier_id].name);
        printf("Название: %s\n", storehouse->products[i].name);
        printf("Цена: %d\n", storehouse->products[i].price);
        printf("Количество: %d\n", storehouse->products[i].count);
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
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "Rus");
    struct Store store = { NULL, 0, NULL, 0, NULL, 0, 0};
    store.num_clients = 0;
    store.num_categories = 0;
    store.num_suppliers = 0;
    store.num_products = 0;
    struct Order order;
    struct Storehouse storehouse;
    struct OrderHistory history;
    history.orderCount = 0;
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
            add_product(&store, &storehouse);
            break;
        case 5:
            create_order(&store, &history, &storehouse);
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
            list_products(&store, &storehouse);
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
