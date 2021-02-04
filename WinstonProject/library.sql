CREATE TABLE Book (
    ISBN int,
    Title varchar(255),
    Author varchar(255),
    Call_Number varchar(255),
    Pages int,
    Binding varchar(255),
    Publisher varchar(255)
    );

CREATE TABLE Loans (
    ISBN int,
    Patron varchar(255)
    );

INSERT INTO Book (ISBN, Title, Author, Call_Number, Pages, Binding, Publisher)
  VALUES (1234567, 'Cheese', 'Michael Eddins', '13131313', 90, 'Paper Back', 'Penguin');

INSERT INTO Book 
  VALUES (8005882300, 'Empire', 'Grant Kelly', '8675309AB', 300, 'Hard Back', 'Publisher2');

INSERT INTO Book
  VALUES (9090909090, 'Some Cool Name', 'Michael Eddins', '182749329248', 1000, 'Periodical', 'Spielburg');

INSERT INTO Loans
  VALUES (90604010, 'Big Chungus');

INSERT INTO Loans
  VALUES (345345894689, 'Epic Style');
