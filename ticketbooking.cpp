#include "TicketBooking.h"

void TicketBooking::addMovie(const std::string& title, const std::string& date, const std::string& day,
    const std::vector<std::string>& availableRooms, int availableSeatsRegular,
    int availableSeatsVIP, double regularPrice, double vipPrice,
    const std::vector<std::string>& availableTimes)
{
    Movie movie;
    movie.title = title;
    movie.date = date;
    movie.day = day;
    movie.availableRooms = availableRooms;
    movie.availableSeatsRegular = availableSeatsRegular;
    movie.availableSeatsVIP = availableSeatsVIP;
    movie.regularPrice = regularPrice;
    movie.vipPrice = vipPrice;
    movie.availableTimes = availableTimes;

    movies.push_back(movie);
}

void TicketBooking::displayMovies()
{
    if (movies.empty())
    {
        std::cout << "Film tidak tersedia." << std::endl;
    }
    else
    {
        std::cout << "Film yang tersedia:" << std::endl;

        for (int i = 0; i < movies.size(); i++)
        {
            std::cout << "Film: " << (i + 1) << ":" << std::endl;
            std::cout << "Judul: " << movies[i].title << std::endl;
            std::cout << "Tanggal: " << movies[i].date << std::endl;
            std::cout << "Hari: " << movies[i].day << std::endl;

            std::cout << "Ruangan yang tersedia:" << std::endl;
            for (int j = 0; j < movies[i].availableRooms.size(); j++)
            {
                std::cout << j + 1 << ". " << movies[i].availableRooms[j] << std::endl;
            }

            std::cout << "Jam tayang yang tersedia:" << std::endl;
            for (int j = 0; j < movies[i].availableTimes.size(); j++)
            {
                std::cout << j + 1 << ". " << movies[i].availableTimes[j] << std::endl;
            }

            std::cout << std::endl;
        }
    }
}

void TicketBooking::displayRooms(int movieIdx)
{
    int idx = movieIdx - 1;

    if (idx >= 0 && idx < movies.size())
    {
        std::cout << "Ruangan yang tersedia untuk film " << movies[idx].title << ":" << std::endl;

        for (int i = 0; i < movies[idx].availableRooms.size(); i++)
        {
            std::cout << i + 1 << ". " << movies[idx].availableRooms[i] << std::endl;
        }
    }
    else
    {
        std::cout << "Salah film." << std::endl;
    }
}

void TicketBooking::displayShowtimes(int movieIdx, int roomIdx)
{
    int idx = movieIdx - 1;
    int roomIndex = roomIdx - 1;

    if (idx >= 0 && idx < movies.size() && roomIndex >= 0 && roomIndex < movies[idx].availableRooms.size())
    {
        std::cout << "Jam tayang yang tersedia untuk film " << movies[idx].title << " dan ruangan " << movies[idx].availableRooms[roomIndex] << ":" << std::endl;

        for (int i = 0; i < movies[idx].availableTimes.size(); i++)
        {
            std::cout << i + 1 << ". " << movies[idx].availableTimes[i] << std::endl;
        }
    }
    else
    {
        std::cout << "Salah film atau ruangan." << std::endl;
    }
}

void TicketBooking::displaySeatAvailability(int movieIdx, int roomIdx)
{
    int idx = movieIdx - 1;
    int roomIndex = roomIdx - 1;

    if (idx >= 0 && idx < movies.size() && roomIndex >= 0 && roomIndex < movies[idx].availableRooms.size())
    {
        std::cout << "Ketersediaan kursi untuk film " << movies[idx].title << " dan ruangan " << movies[idx].availableRooms[roomIndex] << ":" << std::endl;

        // Menampilkan ketersediaan kursi berdasarkan seatAvailability (misalnya, menggunakan 'X' untuk kursi yang tersedia dan '_' untuk kursi yang telah dipesan)
        // Gunakan movies[idx].availableSeatsRegular dan movies[idx].availableSeatsVIP untuk menentukan jumlah kursi yang tersedia

        std::cout << "Regular: ";
        for (int i = 0; i < movies[idx].availableSeatsRegular; i++)
        {
            std::cout << "X ";
        }

        std::cout << std::endl;

        std::cout << "VIP    : ";
        for (int i = 0; i < movies[idx].availableSeatsVIP; i++)
        {
            std::cout << "X ";
        }

        std::cout << std::endl;
    }
    else
    {
        std::cout << "Salah film atau ruangan." << std::endl;
    }
}

void TicketBooking::bookTicket(int movieIdx, int roomIdx, int timeIdx, int quantity, bool isVIP)
{
    int idx = movieIdx - 1;
    int roomIndex = roomIdx - 1;
    int timeIndex = timeIdx - 1;

    if (idx >= 0 && idx < movies.size() && roomIndex >= 0 && roomIndex < movies[idx].availableRooms.size()
        && timeIndex >= 0 && timeIndex < movies[idx].availableTimes.size())
    {
        Movie& movie = movies[idx];

        std::string ticketClass = isVIP ? "VIP" : "Regular";
        std::string showTime = movie.availableTimes[timeIndex];

        std::string theaterRoom = movie.availableRooms[roomIndex];
        int availableSeats = isVIP ? movie.availableSeatsVIP : movie.availableSeatsRegular;
        double ticketPrice = isVIP ? movie.vipPrice : movie.regularPrice;

        if (availableSeats >= quantity)
        {
            double totalPrice = ticketPrice * quantity;

            Ticket ticket;
            ticket.movieTitle = movie.title;
            ticket.date = movie.date;
            ticket.day = movie.day;
            ticket.theaterRoom = theaterRoom;
            ticket.showTime = showTime;
            ticket.quantity = quantity;
            ticket.totalPrice = totalPrice;
            ticket.ticketClass = ticketClass;

            std::vector<int> selectedSeats;
            std::cout << "Pilih kursi yang tersedia (1-" << availableSeats << "): " << std::endl;
            for (int i = 0; i < quantity; i++)
            {
                int seatNumber;
                std::cin >> seatNumber;
                selectedSeats.push_back(seatNumber);
            }

            ticket.seatNumbers = selectedSeats;

            tickets.push_back(ticket);

            if (isVIP)
            {
                movie.availableSeatsVIP -= quantity;
            }
            else
            {
                movie.availableSeatsRegular -= quantity;
            }

            std::cout << "Tiket berhasil dipesan!" << std::endl;
        }
        else
        {
            std::cout << "Tempat duduk tidak tersedia." << std::endl;
        }
    }
    else
    {
        std::cout << "Salah film, ruangan, atau pemilihan waktu." << std::endl;
    }
}

void TicketBooking::displayTickets()
{
    if (tickets.empty())
    {
        std::cout << "Tidak ada tiket yang dipesan." << std::endl;
    }
    else
    {
        std::cout << "Tiket yang dipesan:" << std::endl;

        for (int i = 0; i < tickets.size(); i++)
        {
            std::cout << "Tiket: " << (i + 1) << ":" << std::endl;
            std::cout << "Film: " << tickets[i].movieTitle << std::endl;
            std::cout << "Tanggal: " << tickets[i].date << std::endl;
            std::cout << "Hari: " << tickets[i].day << std::endl;
            std::cout << "Ruangan bioskop: " << tickets[i].theaterRoom << std::endl;
            std::cout << "Jam tayang: " << tickets[i].showTime << std::endl;
            std::cout << "Jumlah: " << tickets[i].quantity << std::endl;
            std::cout << "Total harga: Rp. " << tickets[i].totalPrice << std::endl;
            std::cout << "Kelas tiket: " << tickets[i].ticketClass << std::endl;
            std::cout << "Kursi: ";
            for (int seatNumber : tickets[i].seatNumbers)
            {
                std::cout << seatNumber << " ";
            }
            std::cout << std::endl << std::endl;
        }
    }
}

void TicketBooking::clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

const std::vector<Ticket>& TicketBooking::getTickets() const
{
    return tickets;
}
