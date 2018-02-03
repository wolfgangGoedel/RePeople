WebPack.require("./app.css");

type route =
  | DISCOVER
  | LISTALL;

type action =
  | ToggleRoute
  | PeopleReceived(Model.people);

type state = {
  people: Model.people,
  route
};

let initialState = () => {people: [], route: LISTALL};

let nextRoute =
  fun
  | LISTALL => DISCOVER
  | DISCOVER => LISTALL;

let routeToString =
  fun
  | LISTALL => "Show All"
  | DISCOVER => "Discover";

let reducer = (action, state) =>
  switch action {
  | ToggleRoute => ReasonReact.Update({...state, route: state.route |> nextRoute})
  | PeopleReceived(people) => ReasonReact.Update({...state, people})
  };

let component = ReasonReact.reducerComponent("App");

let peopleReceived = (people) => PeopleReceived(people);

let toggleRoute = (_) => ToggleRoute;

let make = (_children) => {
  ...component,
  initialState,
  reducer,
  didMount: ({reduce}) => {
    Backend.getPeople(peopleReceived |> reduce);
    NoUpdate
  },
  render: ({state: {people, route}, reduce}) =>
    <div className="App">
      <header>
        <AppBar shown=(route |> nextRoute |> routeToString) onClick=(toggleRoute |> reduce) />
      </header>
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