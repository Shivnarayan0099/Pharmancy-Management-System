#include <iostream>
#include <queue>
using namespace std;

struct Medicine {
    int id;
    string name;
    float price;
    int quantity;
    string expiry;
    Medicine* next;
};

Medicine* head = NULL;
queue<string> purchaseQueue;

void addMedicine() {
    int id;
    string name;
    cout << "Enter Medicine ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Medicine Name: ";
    getline(cin, name);
    Medicine* temp = head;
    while (temp != NULL) {
        if (temp->id == id || temp->name == name) {
            cout << "Medicine with same ID or Name already exists\n";
            return;
        }
        temp = temp->next;
    }
    Medicine* newMed = new Medicine();
    newMed->id = id;
    newMed->name = name;
    cout << "Enter Price: ";
    cin >> newMed->price; 
    cout << "Enter Quantity: ";
    cin >> newMed->quantity;
    cout << "Enter Expiry (MM/YY): ";
    cin >> newMed->expiry;
    newMed->next = NULL; 
    if (head == NULL) head = newMed;
    else {
        temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newMed;
    }
    cout << "Medicine added successfully\n";
}
void showMedicines() {
    Medicine* temp = head;
    if (temp == NULL) {
        cout << "No medicines available\n";
        return;
    }
    while (temp != NULL) {
        cout << "\nID: " << temp->id
             << "\nName: " << temp->name
             << "\nPrice: " << temp->price
             << "\nQuantity: " << temp->quantity
             << "\nExpiry: " << temp->expiry << endl;

        temp = temp->next;
    }
}

void searchMedicine() {
    string name;
    cin.ignore();
    cout << "Enter Medicine Name: ";
    getline(cin, name);
    Medicine* temp = head;
    while (temp != NULL) {
        if (temp->name == name) {
            cout << "Medicine Found\n";
            cout << "Price: " << temp->price
                 << "\nQuantity: " << temp->quantity << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Medicine not found\n";
}

void updateMedicine() {
    string name;
    cin.ignore();
    cout << "Enter Medicine Name to update: ";
    getline(cin, name);
    Medicine* temp = head;
    while (temp != NULL) {
        if (temp->name == name) {
            cout << "Enter new Price: ";
            cin >> temp->price;
            cout << "Enter new Quantity: ";
            cin >> temp->quantity;
            cout << "Enter new Expiry: ";
            cin >> temp->expiry;
           cout << "Medicine updated successfully\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Medicine not found\n";
}

void purchaseMedicine() {
    string name;
    int qty;
    cin.ignore();
    cout << "Enter Medicine Name: ";
    getline(cin, name);
    cout << "Enter Quantity to purchase: ";
    cin >> qty;
    Medicine* temp = head;
    while (temp != NULL) {
        if (temp->name == name) {
            if (temp->quantity >= qty) {
                temp->quantity -= qty;
                purchaseQueue.push(temp->name);
                float total = qty * temp->price;
                cout << "\nPurchase successful\n";
                cout << "\n===== BILL =====\n";
                cout << "Medicine: " << temp->name << endl;
                cout << "Quantity: " << qty << endl;
                cout << "Price per unit: " << temp->price << endl;
                cout << "Total Price: " << total << endl;
           } else {
                cout << "Not enough stock\n";
            }
           return;
        }
        temp = temp->next;
    }
   cout << "Medicine not found\n";
}

void showLowStock() {
    Medicine* temp = head;
    bool found = false;
    while (temp != NULL) {
        if (temp->quantity <= 5) {
            cout << temp->name << " LOW STOCK (Qty: "
                 << temp->quantity << ")\n";
            found = true;
        }
        temp = temp->next;
    }
   if (!found) cout << "No medicines in low stock\n";
}

void expiryCheck() {
    int id;
    cout << "Enter Medicine ID: ";
    cin >> id;
    Medicine* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            cout << temp->name << " expiry: " << temp->expiry << endl;
            return;
        }
        temp = temp->next;
    }
   cout << "Medicine not found\n";
}

void dashboard() {
    int count = 0;
    Medicine* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    cout << "\n===== DASHBOARD =====\n";
    cout << "Total Medicines: " << count << endl;
    cout << "Total Purchases: " << purchaseQueue.size() << endl;
}

int main() {
     int choice;
         do {
        cout << "\n===== PHARMACY SYSTEM =====\n";
        cout << "1 Add Medicine\n";
        cout << "2 Show All Medicines\n";
        cout << "3 Search Medicine\n";
        cout << "4 Update Medicine\n";
        cout << "5 Purchase Medicine\n";
        cout << "6 Low Stock Alert\n";
        cout << "7 Expiry Check\n";
        cout << "8 Dashboard\n";
        cout << "9 Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch(choice) {
            case 1: addMedicine(); break;
            case 2: showMedicines(); break;
            case 3: searchMedicine(); break;
            case 4: updateMedicine(); break;
            case 5: purchaseMedicine(); break;
            case 6: showLowStock(); break;
            case 7: expiryCheck(); break;
            case 8: dashboard(); break;
            case 9: cout << "Program ended\n"; break;
            default: cout << "Invalid choice\n";
        }

    } while (choice != 9);

    return 0;
}