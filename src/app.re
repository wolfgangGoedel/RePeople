WebPack.require("./app.css");

type route =
  | DISCOVER
  | LISTALL;

type action =
  | Show(route)
  | PeopleReceived(Model.people);

type state = {
  people: Model.people,
  route
};

let initialState = () => {
  let url = ReasonReact.Router.dangerouslyGetInitialUrl();
  {
    people: [],
    route:
      switch url.path {
      | ["discover"] => DISCOVER
      | _ => LISTALL
      }
  }
};

let reducer = (action, state) =>
  ReasonReact.(
    switch action {
    | Show(route) => Update({...state, route})
    | PeopleReceived(people) => Update({...state, people})
    }
  );

let subscriptions = ({ReasonReact.send}) => [
  ReasonReact.Sub(
    () =>
      ReasonReact.Router.watchUrl(
        (url) =>
          switch url.path {
          | ["all"] => send(Show(LISTALL))
          | ["discover"] => send(Show(DISCOVER))
          | _ => ReasonReact.Router.push("all")
          }
      ),
    ReasonReact.Router.unwatchUrl
  )
];

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState,
  reducer,
  subscriptions,
  didMount: ({send}) => {
    Backend.getPeople((people) => send(PeopleReceived(people)));
    let url = ReasonReact.Router.dangerouslyGetInitialUrl();
    switch url.path {
    | ["all"]
    | ["discover"] => ()
    | _ => ReasonReact.Router.push("all")
    };
    NoUpdate
  },
  render: ({state: {people, route}}) =>
    <div className="App">
      <header> <AppBar /> </header>
      <main>
        (
          switch people {
          | [] => ReasonReact.nullElement
          | _ =>
            switch route {
            | DISCOVER => <Discover people />
            | LISTALL => <ListAll people />
            }
          }
        )
      </main>
    </div>
};