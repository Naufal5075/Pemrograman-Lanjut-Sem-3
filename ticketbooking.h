#ifndef TICKETBOOKING_H
#define TICKETBOOKING_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>

struct Movie {
    std::string title;
    std::string date;
    std::string day;
    std::vector<std::string> availableRooms;
    int availableSeatsRegular;
    int availableSeatsVIP;
    double regularPrice;
    double vipPrice;
    std::vector<std::string> availableTimes;
};

struct Ticket {
    std::string movieTitle;
    std::string date;
    std::string day;
    std::string theaterRoom;
    std::string showTime;
    int quantity;
    double totalPrice;
    std::string ticketClass;
    std::vector<int> seatNumbers;
};

class TicketBooking {
private:
    std::vector<Movie> movies;
    std::vector<Ticket> tickets;
    std::vector<std::vector<bool>> seatAvailability;

    void clearInputBuffer();

public:
    void addMovie(const std::string& title, const std::string& date, const std::string& day,
        const std::vector<std::string>& availableRooms, int availableSeatsRegular,
        int availableSeatsVIP, double regularPrice, double vipPrice,
        const std::vector<std::string>& availableTimes);
    void displayMovies();
    void displayRooms(int movieIdx);
    void displayShowtimes(int movieIdx, int roomIdx);
    void displaySeatAvailability(int movieIdx, int roomIdx);
    void bookTicket(int movieIdx, int roomIdx, int timeIdx, int quantity, bool isVIP);
    void displayTickets();
    const std::vector<Ticket>& getTickets() const;
};

#endif
