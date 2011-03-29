function Path(id, question, text, actions, initActions, conditions, nextLocation) 
{
    this.id = id;
    this.actions = actions;
    this.condition = conditions;
    this.text = text;
    this.question = question;
    this.initActions = initActions;
    this.nextLocation = nextLocation;
}

Path.prototype.id = "";
Path.prototype.actions = "";
Path.prototype.condition = "";
Path.prototype.text = "";
Path.prototype.question = "";
Path.prototype.initActions = "";
Path.prototype.nextLocation = {};
