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
  ReasonReact.(
    switch action {
    | ToggleRoute => Update({...state, route: state.route |> nextRoute})
    | PeopleReceived(people) => Update({...state, people})
    }
  );

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState,
  reducer,
  didMount: ({send}) => {
    Backend.getPeople((people) => send(PeopleReceived(people)));
    NoUpdate
  },
  render: ({state: {people, route}, send}) =>
    <div className="App">
      <header>
        <AppBar shown=(route |> nextRoute |> routeToString) onClick=((_) => send(ToggleRoute)) />
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