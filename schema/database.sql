create table users(id INT generated always as identity, name varchar(255), email varchar(255) unique, password varchar(255));
