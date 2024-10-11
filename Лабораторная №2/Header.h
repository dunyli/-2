// ��������� ��� �������� ������ � �������
struct Client {
    char name[50];
    char phone[20];
    char address[100];
};

// ��������� ��� �������� ������ � ��������� ������
struct Category {
    char name[50];   // �������� ��������� ("����", "�������", "����������")
};

// ��������� ��� �������� ������ � ����������
struct Supplier {
    char name[50];  // �������� ����������
    char address[100];  // ����� ����������
    char phone[20];  // ������� ����������
};

// ��������� ��� �������� ���������� � ������
struct Product {
    char name[50];
    int price;
    int kolvo;
};

// ��������� ��� �������� ���������� � ������
struct Order {
    int client_id;
    struct Product products[100];
    int num_products;
    int total_price;
};

// ��������� ��� �������� ������� �������
struct OrderHistory {
    struct Order orders[100]; // ������ �������
    int orderCount;
    struct Product products[100];
    int num_products;
};

// ��������� ��� �������� ���������� � ��������
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
