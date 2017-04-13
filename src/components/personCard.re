open ReactRe;

module PersonCard = {
  include Component;
  let name = "PersonCard";
  type props = {person: Model.person};
  let render {props: {person}} =>
    <Card>
      <Card.Avatar photoUrl=person.photoUrl />
      <Card.Title
        main=(<a href="#"> (stringToElement (person.firstname ^ " " ^ person.lastname)) </a>)
        sub=(stringToElement person.entity)
      />
      <Card.Info icon="email">
        <a href=("mailto:" ^ person.email)> (stringToElement person.email) </a>
      </Card.Info>
      <Card.Info icon="phone">
        <a href=("tel:" ^ person.phone)> (stringToElement person.phone) </a>
      </Card.Info>
      (
        switch person.manager {
        | Some m =>
          <Card.Info icon="supervisor_account" desc="manager"> (stringToElement m) </Card.Info>
        | None => nullElement
        }
      )
    </Card>;
};

include CreateComponent PersonCard;

let createElement ::person => wrapProps {person: person};