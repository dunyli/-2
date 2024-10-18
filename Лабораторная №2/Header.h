// Структура для хранения данных о клиенте
struct Client {
    char name[50];
    char phone[20];
    char address[100];
};

// Структура для хранения данных о поставщике
struct Supplier {
    struct Product *products;
    char name[50];  // Название поставщика
    char address[100];  // Адрес поставщика
    char phone[20];  // Телефон поставщика
};

// Структура для хранения данных о категории товара
struct Category {
    char name[50];   // Название категории ("Корм", "Игрушки", "Аксессуары")
    struct Product *products;
};

// Структура для хранения информации о товаре
struct Product {
    char name[50];
    int price;
    int count;
    int category_id;
    int supplier_id;
};

// Структура для хранения информации о заказе
struct Order {
    int client_id;
    struct Product *products;
    int num_products;
    int total_price;
    int status_order;
};

// Структура для хранения информации о количестве товара
struct Storehouse {
    struct Product *products;
};

// Структура для хранения истории заказов
struct OrderHistory {
    struct Order *orders; // Массив заказов
    int orderCount;
};

// Структура для хранения информации о магазине
struct Store {
    struct Client *clients;
    int num_clients;
    struct Category *categories;
    int num_categories;
    struct Supplier *suppliers;
    int num_suppliers;
    int num_products;
};
