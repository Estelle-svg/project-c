typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int   id;
    char  name[MAX_NAME_LEN];
    char  category[MAX_CAT_LEN];
    float price;
    int   stock;
    Date  dateAdded;          
} Product;

typedef struct {
    char  name[MAX_NAME_LEN];
    int   isMember;            /* 1 = member, 0 = not a member */
    float balance;             /* money the buyer brings */
} Buyer;

typedef struct {
    Product items[MAX_CART_ITEMS];
    int     quantities[MAX_CART_ITEMS];
    int     itemCount;
} Cart;