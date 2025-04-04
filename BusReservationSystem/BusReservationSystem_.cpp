#include "BusReservationSystem_H.h"


bool Bus::reserveSeat(int seatNumber)
{
    if (seatNumber >= 1 && seatNumber <= totalSeats
        && !seats[seatNumber - 1]) {
        seats[seatNumber - 1] = true;
        return true;
    }
    return false;
}

bool Bus::cancelSeat(int seatNumber)
{
    if (seatNumber >= 1 && seatNumber <= totalSeats
        && seats[seatNumber - 1]) {
        seats[seatNumber - 1] = false;
        return true;
    }
    return false;
}

void Bus::displayBusInfo() const
{
    cout << "\n\t\t\tBus Number: " << busNumber << std::endl;
    cout << "\t\tRoute: " << route.getName() << " ("
        << route.getSource() << " to "
        << route.getDestination() << ")\n";
    cout << "\t\t\tDistance: " << route.getDistance()
        << " km" << std::endl;
    cout << "\t\t\tTotal Seats: " << totalSeats << std::endl;
    cout << "\t\t----- Availabe Seat -----\n";
    bool flag = false;
    for (int i = 0; i < totalSeats; i++) {
        if (!seats[i]) {
            cout << "\t\t" << i + 1;
        }
        else {
            cout << "\t\tNA";
        }
        if (!flag) {
            cout << "\t";
            flag = true;
        }
        else {
            cout << "\n";
            flag = false;
        }
    }
    cout << std::endl;
}

void Bus::displayAvailableSeats() const
{
    cout << "\t\t\tAvailable Seats on Bus " << busNumber
        << ":\n";
    for (int i = 0; i < totalSeats; ++i) {
        if (seats[i]) {
            cout << "\t\t\tSeat " << i + 1
                << ": Available\n";
        }
    }
}

void Bus::displayBusStatus() const
{
    int reservedSeats = 0;
    for (int i = 0; i < totalSeats; ++i) {
        if (seats[i]) {
            reservedSeats++;
        }
    }

    cout << "Bus Status for Bus " << busNumber << ":\n";
    cout << "Total Seats: " << totalSeats << "\n";
    cout << "Reserved Seats: " << reservedSeats << "\n";
    cout << "Available Seats: "
        << totalSeats - reservedSeats << "\n";
}

void User::removeTicket(int index)
{
    std::vector<Ticket>::iterator i = tickets.begin();
    i = i + index - 1;
    tickets.erase(i);
}

void User::printAllTickets() const
{
    int i = 0;
    for (i = 0; i < tickets.size(); i++) {
        cout << "\n\t\t------ Ticket " << i + 1
            << " ------" << std::endl;
        cout << "\t\t\tPassenger: "
            << tickets[i].getPassengerName() << std::endl;
        cout << "\t\tRoute: "
            << tickets[i].getRoute().getName() << " ("
            << tickets[i].getRoute().getSource()
            << " to "
            << tickets[i].getRoute().getDestination()
            << ")\n";
        cout << "\t\t\tBus Number: "
            << tickets[i].getBus().getBusNumber()
            << std::endl;
        cout << "\t\t\tSeat Number: "
            << tickets[i].getSeatNumber() << std::endl;
    }
}

BusReservationSystem::BusReservationSystem()
{
    routes.push_back(
        Route("E58", "Bratislava", "Trnava", 57));
    routes.push_back(
        Route("E75", "Trnava", "Zilina", 158));
    routes.push_back(
        Route("E50", "Zilina", "Kosice", 253));

    buses.push_back(Bus("B001", routes[0], 20));
    buses.push_back(Bus("B002", routes[1], 15));
    buses.push_back(Bus("B003", routes[2], 18));
}

void BusReservationSystem::registerUser(const std::string& username,
    const std::string& password)
{
    users.push_back(User(username, password));
    cout << "\n\t\tUser registered successfully. "
        "Please login to continue!\n";
}

bool BusReservationSystem::authenticateUser(const std::string& username,
    const std::string& password)
{
    for (const User& user : users) {
        std::string lowercaseUsername = user.getUsername();
        std::string lowercaseInputUsername = username;
        transform(lowercaseUsername.begin(),
            lowercaseUsername.end(),
            lowercaseUsername.begin(), ::tolower);
        transform(lowercaseInputUsername.begin(),
            lowercaseInputUsername.end(),
            lowercaseInputUsername.begin(),
            ::tolower);

        if (lowercaseUsername == lowercaseInputUsername
            && user.getPassword() == password) {
            return true;
        }
    }
    return false;
}

void BusReservationSystem::displayRoutes() const
{
    system("cls");

    cout << "\n\t\t------ Available Routes ------\n";
    for (const Route& route : routes) {
        cout << "\n\t\tRoute Name: " << route.getName()
            << " (" << route.getSource() << " to "
            << route.getDestination() << ")\n";
        cout << "\t\t\tDistance: "
            << route.getDistance() << " km" << std::endl;
    }
}

void BusReservationSystem::displayBuses() const
{
    system("cls");

    cout << "\t\t------ Available Buses ------\n";
    for (const Bus& bus : buses) {
        bus.displayBusInfo();
        cout << std::endl;
    }
}

void BusReservationSystem::displayBusesForRoute(int selectedRoute) const
{
    cout << "\t\t\tBuses available for Route "
        << routes[selectedRoute - 1].getName()
        << ":\n";
    for (int i = 0; i < buses.size(); i++) {
        if (buses[i].getRoute().getName()
            == routes[selectedRoute - 1].getName()) {
            buses[i].displayBusInfo();
            cout << std::endl;
        }
    }
}

void BusReservationSystem::bookTicket(const std::string& username)
{
    int selectedRoute, selectedBus, selectedSeat;

    displayRoutes();
    cout << "\n\t\tSelect a Route (Enter the Route "
        "Number): ";
    std::string routeNumber;
    cin >> routeNumber;

    bool validRoute = false;
    for (int i = 0; i < routes.size(); i++) {
        if (routeNumber == routes[i].getName()) {
            selectedRoute = i + 1;
            validRoute = true;
            break;
        }
    }

    if (!validRoute) {
        cout << "\n\tInvalid route number. Please "
            "enter a valid route number.\n";
        return; // Return to the main menu
    }

    // Consume the newline character
    cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');

    displayBusesForRoute(selectedRoute);

    cout << "\n\t\tSelect a Bus (Enter the Bus "
        "Number): ";
    std::string busNumber;
    cin >> busNumber;

    validRoute = false;
    for (int i = 0; i < buses.size(); i++) {
        if (busNumber == buses[i].getBusNumber()
            && buses[i].getRoute().getName()
            == routes[selectedRoute - 1]
            .getName()) {
            selectedBus = i + 1;
            validRoute = true;
            break;
        }
    }

    if (!validRoute) {
        cout << "\n\tInvalid bus number. Please enter "
            "a valid bus number for the selected "
            "route.\n";
        return; // Return to the main menu
    }

    // Consume the newline character
    cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');

    cout << "\n\t\tEnter the seat number you want to "
        "book: ";
    cin >> selectedSeat;

    if (cin.fail() || selectedSeat < 1
        || selectedSeat > buses[selectedBus - 1]
        .getTotalSeats()) {
        cout << "\n\tInvalid seat number. Please enter "
            "a valid seat number for the selected "
            "bus.\n";
        return; // Return to the main menu
    }

    if (buses[selectedBus - 1].reserveSeat(
        selectedSeat)) {
        Ticket ticket(username, selectedSeat,
            routes[selectedRoute - 1],
            buses[selectedBus - 1]);
        User& user = findUser(username);
        user.addTicket(ticket);
        cout << "\n\t\t\tTicket booked successfully!\n";
        cout << "\t\t\tPassenger: "
            << ticket.getPassengerName() << "\n";
        cout << "\t\t\tBus Number: "
            << buses[selectedBus - 1].getBusNumber()
            << "\n";
        cout << "\t\t\tRoute: "
            << ticket.getRoute().getName() << " ("
            << ticket.getRoute().getSource() << " to "
            << ticket.getRoute().getDestination()
            << ")\n";
        cout << "\t\t\tSeat Number: "
            << ticket.getSeatNumber() << "\n";
        buses[selectedBus - 1].displayBusStatus();
    }
    else {
        cout << "\n\tSeat booking failed. The seat is "
            "already reserved or does not exist.\n";
    }
}

void BusReservationSystem::cancelTicket(const std::string& username)
{
    int ticketDel = -1;
    User& user = findUser(username);
    if (user.numberOfTickets() <= 0) {
        cout << "\n\t\t\nNo Tickets Booked!\n";
        return;
    }
    user.printAllTickets();

    cout << "\t\t\nSelect the ticked to be "
        "cancelled... ";
    cin >> ticketDel;

    // Consume the newline character
    cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');

    if (cin.fail()
        || ticketDel > user.numberOfTickets()) {
        cout << "\tInvalid Ticked Selected! Please "
            "select a valid ticket\n";
        return;
    }
    else {
        cout << "\t\t\tTicket canceled successfully.\n";
        Ticket ticket = user.getTicket(ticketDel);
        Bus bus = ticket.getBus();
        for (int i = 0; i < buses.size(); i++) {
            if (buses[i].getBusNumber()
                == bus.getBusNumber()) {
                buses[i].cancelSeat(
                    ticket.getSeatNumber());
            }
        }
        user.removeTicket(ticketDel);
    }
}

void BusReservationSystem::run()
{
    system("cls");

    while (true) {
        cout << "\n\t------ Welcome to the Bus "
            "Reservation System------\n\n";
        cout << "\t\t\t1. Register\n\t\t\t2. Log "
            "In\n\t\t\t3. Exit\t\t\t\n";
        cout << "\n\t\t\tEnter your choice: ";
        int choice;
        cin >> choice;
		cin.get(); // Consume the newline character

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "\t\t\tEnter number only\n";
            cin >> choice;
            cin.get(); // Consume the newline character
        }

        if (choice == 1) {
            std::string username, password;
            cout << "\n\t\t\tEnter username: ";
            std::getline(std::cin, username);
            cout << "\t\t\tEnter password (no spaces): ";
            cin >> password;
            registerUser(username, password);
        }
        else if (choice == 2) {
            std::string username, password;
            cout << "\n\t\t\tEnter username: ";
            std::getline(std::cin, username);
            cout << "\t\t\tEnter password (no spaces): ";
            cin >> password;
            if (authenticateUser(username, password)) {
                cout << "\n\t\t\tLogged in "
                    "successfully!\n";
                userMenu(username);
            }
            else {
                cout << "\n\t\tAuthentication failed! "
                    "Please check your username "
                    "and password.\n";
            }
        }
        else if (choice == 3) {
            cout << "\n\t\tExiting the Bus Reservation "
                "System. Goodbye!\n";
            break;
        }
    }
}

void BusReservationSystem::userMenu(std::string username)
{
    int choice = 0;
    while (true) {
        cout << "\n\t-----------  Welcome to the User "
            "Menu  ------------\n\n";
        cout << "\t\t\t1. Display Routes\n"
            "\t\t\t2. Display Buses\n"
            "\t\t\t3. Book Ticket\n"
            "\t\t\t4. Cancel Ticket\n"
            "\t\t\t5. Logout\n\n";
        cout << "\n\t\t\tEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            displayRoutes();
        }
        else if (choice == 2) {
            displayBuses();
        }
        else if (choice == 3) {
            bookTicket(username);
        }
        else if (choice == 4) {
            cancelTicket(username);
        }
        else if (choice == 5) {
            cout
                << "\n\t\t\tLogged out successfully.\n";
            break;
        }
    }
}