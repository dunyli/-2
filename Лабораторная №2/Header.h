// Структура для хранения данных о клиенте
struct Client {
    char name[50];
    char phone[20];
    char address[100];
};

// Структура для хранения данных о категории товара
struct Category {
    char name[50];   // Название категории ("Корм", "Игрушки", "Аксессуары")
};

// Структура для хранения данных о поставщике
struct Supplier {
    char name[50];  // Название поставщика
    char address[100];  // Адрес поставщика
    char phone[20];  // Телефон поставщика
};

// Структура для хранения информации о товаре
struct Product {
    char name[50];
    int price;
    int kolvo;
};

// Структура для хранения информации о заказе
struct Order {
    int client_id;
    struct Product products[100];
    int num_products;
    int total_price;
};

// Структура для хранения истории заказов
struct OrderHistory {
    struct Order orders[100]; // Массив заказов
    int orderCount;
    struct Product products[100];
    int num_products;
};

// Структура для хранения информации о магазине
struct Store {
    struct Client clients[100];
    int num_clients;
    struct Category categories[20];
    int num_categories;
    struct Supplier suppliers[50];
    int num_supplier;
    struct Product products[100];
    int num_products;
};
