# Technical Implementation

## OOP Design

The system has been built using object-oriented programming principles:

- **Encapsulation**: Data and methods are encapsulated within their respective classes
- **Abstraction**: Complex operations are abstracted into simple methods
- **Single Responsibility**: Each class has a specific responsibility
- **Separation of Concerns**: Business logic is separate from file I/O and UI

## Classes

1. **Account**: Represents a user account with personal information and order history
2. **Product**: Represents a product with inventory and audit information
3. **CartItem**: Represents an item in the shopping cart
4. **ShoppingCart**: Manages the collection of cart items
5. **FileManager**: Handles all file I/O operations
6. **AuthManager**: Manages user authentication and sessions
7. **ProductManager**: Handles product operations and inventory
8. **CheckoutManager**: Processes checkout operations
9. **ReportGenerator**: Generates various reports
10. **ECommerceSystem**: Main controller that coordinates between different classes

## Class Relationships

```
               ┌───────────────┐
               │ECommerceSystem│
               └───────┬───────┘
                       │
       ┌───────────────┼───────────────┐
       │               │               │
┌──────▼─────┐  ┌──────▼─────┐  ┌──────▼─────┐
│AuthManager │  │ProductMgr  │  │ShoppingCart│
└──────┬─────┘  └──────┬─────┘  └──────┬─────┘
       │               │               │
┌──────▼─────┐  ┌──────▼─────┐  ┌──────▼─────┐
│  Account   │  │  Product   │  │ CartItem   │
└────────────┘  └────────────┘  └────────────┘
       │               │
       └───────┐ ┌─────┘
               │ │
          ┌────▼─▼────┐     ┌─────────────┐
          │FileManager│◄────┤CheckoutMgr  │
          └───────────┘     └──────┬──────┘
                                   │
                            ┌──────▼──────┐
                            │ReportGen    │
                            └─────────────┘
```

## File Management

The system uses several files to persist data:
- `accounts.txt`: User account data
- `products.txt`: Product catalog data
- `invoice.txt`: Latest invoice
- `history.txt`: Purchase history
- `product_audit.txt`: Audit trail for product changes
