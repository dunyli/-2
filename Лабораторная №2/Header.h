// ��������� ��� �������� ������ � �������
struct Client {
    char name[50];
    char phone[20];
    char address[100];
};

// ��������� ��� �������� ������ � ����������
struct Supplier {
    struct Product *products;
    char name[50];  // �������� ����������
    char address[100];  // ����� ����������
    char phone[20];  // ������� ����������
};

// ��������� ��� �������� ������ � ��������� ������
struct Category {
    char name[50];   // �������� ��������� ("����", "�������", "����������")
    struct Product *products;
};

// ��������� ��� �������� ���������� � ������
struct Product {
    char name[50];
    int price;
    int count;
    int category_id;
    int supplier_id;
};

// ��������� ��� �������� ���������� � ������
struct Order {
    int client_id;
    struct Product *products;
    int num_products;
    int total_price;
    int status_order;
};

// ��������� ��� �������� ���������� � ���������� ������
struct Storehouse {
    struct Product *products;
};

// ��������� ��� �������� ������� �������
struct OrderHistory {
    struct Order *orders; // ������ �������
    int orderCount;
};

// ��������� ��� �������� ���������� � ��������
struct Store {
    struct Client *clients;
    int num_clients;
    struct Category *categories;
    int num_categories;
    struct Supplier *suppliers;
    int num_suppliers;
    int num_products;
};
