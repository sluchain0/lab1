#include <iostream>
#include <string>
#include <memory>
#include <string>

/*Node:
   - Структура Node определяет узел списка с полями для имени,
   идентификатора (ID), значения и указателя на следующий узел*/

struct Node {
    std::string name;
    int id;
    double value;
    std::shared_ptr<Node> next;
};

/* insertAtFront:
   - Функция добавляет новый узел в начало списка*/

void insertAtFront(std::shared_ptr<Node>& head, const std::string& name, int id, double value) {
    auto newNode = std::make_shared<Node>();
    newNode->name = name;
    newNode->id = id;
    newNode->value = value;
    newNode->next = head;
    head = newNode;
}

/*append:
   - Функция добавляет новый узел в конец списка*/

void append(std::shared_ptr<Node>& head, const std::string& name, int id, double value) {
    auto newNode = std::make_shared<Node>();
    newNode->name = name;
    newNode->id = id;
    newNode->value = value;
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
    }
    else {
        auto current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

/* insertAfter:
- Функция добавляет новый узел после указанного элемента в списке.*/

void insertAfter(std::shared_ptr<Node>& head, const std::string& targetName, const std::string& name, int id, double value) {
    auto current = head;
    while (current && current->name != targetName) {
        current = current->next;
    }

    if (current) {
        auto newNode = std::make_shared<Node>();
        newNode->name = name;
        newNode->id = id;
        newNode->value = value;
        newNode->next = current->next;
        current->next = newNode;
    }
}


/*insertBefore:
   - Функция добавляет новый узел перед указанным элементом в списке.*/

void insertBefore(std::shared_ptr<Node>& head, const std::string& targetName, const std::string& name, int id, double value) {
    if (!head || head->name == targetName) {
        insertAtFront(head, name, id, value);
        return;
    }

    auto current = head;
    while (current->next && current->next->name != targetName) {
        current = current->next;
    }

    if (current->next) {
        auto newNode = std::make_shared<Node>();
        newNode->name = name;
        newNode->id = id;
        newNode->value = value;
        newNode->next = current->next;
        current->next = newNode;
    }
}

/*removeByName:
   - Функция удаляет узел с заданным именем из списка.*/

void removeByName(std::shared_ptr<Node>& head, const std::string& name) {
    if (!head) return;

    if (head->name == name) {
        head = head->next;
        return;
    }

    auto current = head;
    while (current->next && current->next->name != name) {
        current = current->next;
    }

    if (current->next) {
        current->next = current->next->next;
    }
}

/*displayList:
   - Функция отображает содержимое списка на экране.*/

void displayList(const std::shared_ptr<Node>& head) {
    auto current = head;
    while (current) {
        std::cout << "Name: " << current->name << ", ID: " << current->id << ", Value: " << current->value << std::endl;
        current = current->next;
    }
}

/*В функции main создается список узлов и осуществляются операции добавления и удаления узлов из списка,
а также вывод списка после каждого изменения.*/

int main() {
    std::shared_ptr<Node> head = nullptr;

    append(head, "First", 1, 1.1);
    append(head, "Second", 2, 2.2);
    insertAtFront(head, "Zeroth", 0, 0.0);
    insertAfter(head, "First", "Between", 1, 1.5);
    insertBefore(head, "Second", "BeforeSecond", 1, 1.75);

    std::cout << "List after additions:" << std::endl;
    displayList(head);

    removeByName(head, "Between");
    std::cout << "List after deletion:" << std::endl;
    displayList(head);

    return 0;
}