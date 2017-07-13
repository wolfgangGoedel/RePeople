Random.self_init ();

type state = {
  currentPersonId: int,
  timerId: option Js.Global.intervalId
};

let component = ReasonReact.statefulComponent "Discover";

let make ::people _children => {
  let succ n => n == Array.length people - 1 ? 0 : n + 1;
  let nextPerson _ {ReasonReact.state: state} =>
    ReasonReact.Update {...state, currentPersonId: succ state.currentPersonId};
  {
    ...component,
    initialState: fun () => {currentPersonId: 0, timerId: None},
    didMount: fun {state, update} =>
      ReasonReact.SilentUpdate {
        ...state,
        timerId: Some (Js.Global.setInterval (update nextPerson) 2000)
      },
    willUnmount: fun {state} =>
      switch state.timerId {
      | Some id => Js.Global.clearInterval id
      | None => ()
      },
    render: fun {state} => <PersonCard person=people.(state.currentPersonId) />
  }
};