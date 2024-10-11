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
