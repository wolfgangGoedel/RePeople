Utils.import "../style/discover.css";

Random.self_init ();

module Fab = {
  let component = ReasonReact.statelessComponent "Fab";
  let make ::kind ::size=? ::onClick _children => {
    let sizeClass =
      switch size {
      | Some s => " btn-" ^ s
      | None => ""
      };
    {
      ...component,
      render: fun _ =>
        <a className=("btn-default btn-floating waves-effect waves-light" ^ sizeClass) onClick>
          <i className="material-icons"> (ReasonReact.stringToElement kind) </i>
        </a>
    }
  };
};

type actions =
  | ShowNext
  | ShowPrev
  | Play
  | Pause;

type state = {
  currentPersonId: int,
  isPlaying: bool,
  intervalId: ref (option Js.Global.intervalId)
};

let initialState nbPeople () => {
  currentPersonId: Random.int nbPeople + 1,
  isPlaying: false,
  intervalId: ref None
};

let showNext _ => ShowNext;

let showPrev _ => ShowPrev;

let play _ => Play;

let pause _ => Pause;

let succ max n => n >= max ? 1 : n + 1;

let pred max n => n <= 1 ? max : n - 1;

let setNext nbPeople state => {...state, currentPersonId: succ nbPeople state.currentPersonId};

let setPrev nbPeople state => {...state, currentPersonId: pred nbPeople state.currentPersonId};

let setPlaying isPlaying state => {...state, isPlaying};

let stopInterval self => {
  let state = self.ReasonReact.state;
  switch !state.intervalId {
  | Some iid =>
    Js.Global.clearInterval iid;
    state.intervalId := None
  | None => ()
  }
};

let startInterval self => {
  stopInterval self;
  ReasonReact.(self.state.intervalId := Some (Js.Global.setInterval (self.reduce showNext) 2000))
};

let reducer nbPeople action state =>
  switch action {
  | ShowNext => ReasonReact.Update (state |> setNext nbPeople)
  | ShowPrev => ReasonReact.Update (state |> setPrev nbPeople)
  | Play =>
    ReasonReact.UpdateWithSideEffects (state |> setNext nbPeople |> setPlaying true) startInterval
  | Pause => ReasonReact.UpdateWithSideEffects (state |> setPlaying false) stopInterval
  };

let component = ReasonReact.reducerComponent "Discover";

let make ::people _children => {
  let aPeople = Array.of_list people;
  let nbPeople = Array.length aPeople;
  {
    ...component,
    initialState: initialState nbPeople,
    reducer: reducer nbPeople,
    willUnmount: stopInterval,
    render: fun {state, reduce} =>
      <div className="Discover">
        <div className="card-container">
          <PersonCard person=aPeople.(state.currentPersonId - 1) />
        </div>
        <div className="fab-container">
          <Fab kind="skip_previous" onClick=(reduce showPrev) />
          (
            state.isPlaying ?
              <Fab kind="pause" size="large" onClick=(reduce pause) /> :
              <Fab kind="play_arrow" size="large" onClick=(reduce play) />
          )
          <Fab kind="skip_next" onClick=(reduce showNext) />
        </div>
      </div>
  }
};
