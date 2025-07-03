This is a C++ console application allows users to register, log in, and book seats for movie shows in different cinemas.
Features
- 👤 User registration and login
- 🧑‍💼 Admin panel with password access (`root123`)
- 🎥 Admin can:
  - Add new movies and showtimes
  - Manage cinemas
- 🎟️ Users can:
  - View available cinemas and movies
  - Select showtimes and book seats
  - Review previous bookings
- 🪑 Seat booking system with visual layout
- Data persistence (saved to `.json` files)

  <h2>File Structure</h2>
<pre>
├── adminpanel
|   ├── admin.h
|   ├── movies.json
|   └── admin.cpp
├── auth/
│   ├── auth.cpp
│   └── auth.h
│
├── booking/
│   ├── booking.cpp
│   └── bookings.json
│
├── json/
│   ├── json.cpp
│   └── json.hpp
│
├── main/
│   └── main.cpp
│
└── menu/
|   ├── menu.cpp
|   ├── seat.cpp
|   ├── menu.h
|   └── menu.h
└── README.md
</pre>

<h2>Technologies Used</h2>
<ul>
  <li><strong>C++17</strong></li>
  <li><strong>Visual Studio 2022</strong></li>
  <li><strong>Git & GitHub</strong></li>
</ul>
