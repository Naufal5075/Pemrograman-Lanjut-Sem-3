#include <iostream>
#include <fstream>
#include "TicketBooking.h"

int choice;
int movieIndex;
int roomIndex;
int timeIndex;
int quantity;
bool isVIP;

void printTicketsToFile(const std::vector<Ticket>& tickets) {
    std::ofstream outputFile("booked_tickets.txt");
    if (outputFile.is_open()) {
        for (const Ticket& ticket : tickets) {
            outputFile << "Film: " << ticket.movieTitle << std::endl;
            outputFile << "Tanggal: " << ticket.date << std::endl;
            outputFile << "Hari: " << ticket.day << std::endl;
            outputFile << "Ruangan bioskop: " << ticket.theaterRoom << std::endl;
            outputFile << "Jam tayang: " << ticket.showTime << std::endl;
            outputFile << "Jumlah: " << ticket.quantity << std::endl;
            outputFile << "Total harga: Rp. " << ticket.totalPrice << std::endl;
            outputFile << "Kelas tiket: " << ticket.ticketClass << std::endl;
            outputFile << "Kursi: ";
            for (int seatNumber : ticket.seatNumbers) {
                outputFile << seatNumber << " ";
            }
            outputFile << std::endl << std::endl;
        }
        std::cout << "Tiket berhasil dicetak dalam file booked_tickets.txt" << std::endl;
        outputFile.close();
    }
    else {
        std::cout << "Gagal membuka file untuk mencetak tiket." << std::endl;
    }
}

int main() {
    TicketBooking ticketBooking;

    // Menambahkan detail film
    ticketBooking.addMovie("Avengers: Endgame", "2023-06-21", "Senin", { "Room 1", "Room 2" }, 50, 100, 40, 80, { "10:00", "14:00", "18:00" });
    ticketBooking.addMovie("The Lion King", "2023-06-22", "Selasa", { "Room 3", "Room 4" }, 40, 80, 30, 60, { "11:00", "15:00", "19:00" });
    ticketBooking.addMovie("Joker", "2023-06-23", "Rabu", { "Room 5", "Room 6" }, 45, 90, 35, 70, { "12:00", "16:00", "20:00" });
    ticketBooking.addMovie("Spider-Man: Far From Home", "2023-06-24", "Kamis", { "Room 7", "Room 8" }, 48, 95, 38, 76, { "13:00", "17:00", "21:00" });
    ticketBooking.addMovie("Wonder Woman 1984", "2023-06-25", "Jumat", { "Room 9", "Room 10" }, 42, 85, 33, 66, { "14:00", "18:00", "22:00" });

    while (true) {
        std::cout << "===============================" << std::endl;
        std::cout << "          TIKET BIOSKOP        " << std::endl;
        std::cout << "===============================" << std::endl;
        std::cout << "1. Tampilkan Film" << std::endl;
        std::cout << "2. Beli Tiket" << std::endl;
        std::cout << "3. Tampilkan Tiket yang telah dibeli" << std::endl;
        std::cout << "4. Cetak Tiket ke File" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "===============================" << std::endl;
        std::cout << "Masukkan Pilihan [1/2/3/4/0]: ";
        std::cin >> choice;

        switch (choice) {
        case 0:
            std::cout << "Terima kasih telah menggunakan aplikasi kami!" << std::endl;
            return 0;

        case 1:
            ticketBooking.displayMovies();
            break;

        case 2:
            ticketBooking.displayMovies();

            std::cout << "Pilih film yang ingin ditonton [1/2/3/4/5]: ";
            std::cin >> movieIndex;

            ticketBooking.displayRooms(movieIndex);

            std::cout << "Pilih ruangan [1/2]: ";
            std::cin >> roomIndex;

            ticketBooking.displayShowtimes(movieIndex, roomIndex);

            std::cout << "Pilih jam tayang [1/2/3]: ";
            std::cin >> timeIndex;

            std::cout << "Masukkan jumlah tiket: ";
            std::cin >> quantity;

            std::cout << "Apakah anda berminat untuk membeli tiket VIP (1 untuk ya, 0 untuk tidak): ";
            std::cin >> isVIP;

            ticketBooking.bookTicket(movieIndex, roomIndex, timeIndex, quantity, isVIP);
            break;

        case 3:
            ticketBooking.displayTickets();
            break;

        case 4:
            ticketBooking.displayTickets();
            if(!ticketBooking.getTickets().empty())
            {
                printTicketsToFile(ticketBooking.getTickets());
            } else
            {
                std::cout << "Tidak dapat print tiket." << std::endl;
            }
            break;

        default:
            std::cout << "Pilihan tidak tersedia, silakan coba lagi." << std::endl;
            break;
        }
    }

    return 0;
}
