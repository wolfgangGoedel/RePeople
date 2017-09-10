type person = {
  id: string,
  firstname: string,
  lastname: string,
  photoUrl: string,
  entity: string,
  email: string,
  phone: string,
  manager: option string
};

type people = list person;
