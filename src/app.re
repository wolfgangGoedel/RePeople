WebPack.require("./app.css");

type route =
  | DISCOVER
  | LISTALL
  | UNKNOWN;

let matchRoute = (url: ReasonReact.Router.url) =>
  switch url.path {
  | ["discover"] => DISCOVER
  | ["all"] => LISTALL
  | _ => UNKNOWN
  };

type action =
  | Show(route)
  | PeopleReceived(Model.people);

type state = {
  people: Model.people,
  route
};

let initialState = () => {
  people: [],
  route: ReasonReact.Router.dangerouslyGetInitialUrl() |> matchRoute
};

let reducer = (action, state) =>
  ReasonReact.(
    switch action {
    | Show(route) => Update({...state, route})
    | PeopleReceived(people) => Update({...state, people})
    }
  );

let subscriptions =
  ReasonReact.(
    ({send}) => [
      Sub(
        () =>
          Router.watchUrl(url =>
            url |> matchRoute |> (route => Show(route) |> send)
          ),
        Router.unwatchUrl
      )
    ]
  );

module Redirect {
  let component = ReasonReact.statelessComponent("Redirect");
  let make = (~toPath, _children) => {
    ...component,
    didMount: _ => {
      ReasonReact.Router.push(toPath);
      NoUpdate;
    }
  }
};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState,
  reducer,
  subscriptions,
  didMount: ({send}) => {
    Backend.getPeople(people => send(PeopleReceived(people)));
    NoUpdate;
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
            | UNKNOWN => <Redirect toPath="/all" />
            }
          }
        )
      </main>
    </div>
};