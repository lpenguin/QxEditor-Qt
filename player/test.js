//!bs:ql.param(var(Vremya), var(18))
Vremya = 18;AddToVars('Vremya');
//!bs:ql.cons(var(Vremya), val(0), val(18))
AddConstraint('Vremya', 0, 18);
//!bs:end
//!bs:ql.show(var(Vremya), [ran(val(0),val(0)), ran(val(1),val(1)), ran(val(2),val(4)), ran(val(5),val(18))], ['Время вышло', 'Остался <> час', 'Осталось <> часа', 'Осталось <> часов'], 1 )
AddShowRanges('Vremya', [range(0, 0),range(1, 1),range(2, 4),range(5, 18)], ['Время вышло','Остался <> час','Осталось <> часа','Осталось <> часов'], 1);
//!bs:end
//!bs:ql.icons(var(Vremya))
AddIntConstraint('Vremya');
//!bs:end
//!bs:ql.bound(var(Vremya), max, val(18), 'К сожалению&comm; вы не смогли завершить Церемонию Переправы на Лодке до рассвета&comm; и голограмма пропала&comm; как только первые лучи восходящего солнца коснулись стен пирамиды. Господин Хуу&comm; впрочем&comm; выглядел не очень расстроенным.&rl;&nl;&rl;&nl;- Я не очень-то и верил в ваш успех&comm; - признался он вам. - Что ж&comm; спасибо хотя бы за попытку! Придется попросить о помощи кого-нибудь другого. &rl;&nl;&rl;&nl;Попрощавшись с археологом&comm; вы вернулись на свой корабль.')
AddBound('Vremya','max', 18, 'К сожалению, вы не смогли завершить Церемонию Переправы на Лодке до рассвета, и голограмма пропала, как только первые лучи восходящего солнца коснулись стен пирамиды. Господин Хуу, впрочем, выглядел не очень расстроенным.\\n\\n- Я не очень-то и верил в ваш успех, - признался он вам. - Что ж, спасибо хотя бы за попытку! Придется попросить о помощи кого-нибудь другого. \\n\\nПопрощавшись с археологом, вы вернулись на свой корабль.');
//!bs:end
//!bs:end
//!bs:ql.param(var(Sprava), var(0))
Sprava = 0;AddToVars('Sprava');
//!bs:ql.cons(var(Sprava), val(0), val(4))
AddConstraint('Sprava', 0, 4);
//!bs:end
//!bs:ql.show(var(Sprava), [ran(val(0),val(4))], ['Положение Богов:'], 1 )
AddShowRanges('Sprava', [range(0, 4)], ['Положение Богов:'], 1);
//!bs:end
//!bs:ql.icons(var(Sprava))
AddIntConstraint('Sprava');
//!bs:end
//!bs:ql.bound(var(Sprava), max, val(4), 'Как только все &dq;Боги&dq; оказались на правой стороне реки&comm; обсидиановая плита в дальнем конце зала бесшумно выдвинулась вперёд и отошла в сторону. Вы вошли в открывшийся проход и увидели однообразные ряды огромных обсидиановых плит в несколько метров высотой&comm; прикосновение к которым вызывало появление на их поверхности постоянно меняющейся вязи из мелких и непонятных белых значков. Что ж&comm; если это действительно библиотека Ваа&comm; то расшифровка их языка и поиск нужных сведений может затянуться на столетия. Но вас это&comm; впрочем&comm; не касается - свою часть работы вы сделали и можете лететь на <FromPlanet> за заслуженной наградой... &rl;&nl;&rl;&nl;Попрощавшись с учеными&comm; при виде пресловутых плит забывшими обо всем на свете&comm; вы вернулись на свой корабль.')
AddBound('Sprava','max', 4, 'Как только все "Боги" оказались на правой стороне реки, обсидиановая плита в дальнем конце зала бесшумно выдвинулась вперёд и отошла в сторону. Вы вошли в открывшийся проход и увидели однообразные ряды огромных обсидиановых плит в несколько метров высотой, прикосновение к которым вызывало появление на их поверхности постоянно меняющейся вязи из мелких и непонятных белых значков. Что ж, если это действительно библиотека Ваа, то расшифровка их языка и поиск нужных сведений может затянуться на столетия. Но вас это, впрочем, не касается - свою часть работы вы сделали и можете лететь на <FromPlanet> за заслуженной наградой... \\n\\nПопрощавшись с учеными, при виде пресловутых плит забывшими обо всем на свете, вы вернулись на свой корабль.');
//!bs:end
//!bs:end
//!bs:ql.param(var(Ah(2)), var(0))
Ah(2) = 0;AddToVars('Ah(2)');
//!bs:ql.cons(var(Ah(2)), val(0), val(1))
AddConstraint('Ah(2)', 0, 1);
//!bs:end
//!bs:ql.show(var(Ah(2)), [ran(val(0),val(0)), ran(val(1),val(1))], ['Ах &lb;2&rb; - xxx', 'xxx - Ах&lb;2&rb;'], 1 )
AddShowRanges('Ah(2)', [range(0, 0),range(1, 1)], ['Ах (2) - xxx','xxx - Ах(2)'], 1);
//!bs:end
//!bs:ql.icons(var(Ah(2)))
AddIntConstraint('Ah(2)');
//!bs:end
//!bs:end
//!bs:ql.param(var(Bah(5)), var(0))
Bah(5) = 0;AddToVars('Bah(5)');
//!bs:ql.cons(var(Bah(5)), val(0), val(1))
AddConstraint('Bah(5)', 0, 1);
//!bs:end
//!bs:ql.show(var(Bah(5)), [ran(val(0),val(0)), ran(val(1),val(1))], ['Бах &lb;5&rb; - xxx', 'xxx - Бах&lb;5&rb;'], 1 )
AddShowRanges('Bah(5)', [range(0, 0),range(1, 1)], ['Бах (5) - xxx','xxx - Бах(5)'], 1);
//!bs:end
//!bs:ql.icons(var(Bah(5)))
AddIntConstraint('Bah(5)');
//!bs:end
//!bs:end
//!bs:ql.param(var(Vau(1)), var(0))
Vau(1) = 0;AddToVars('Vau(1)');
//!bs:ql.cons(var(Vau(1)), val(0), val(1))
AddConstraint('Vau(1)', 0, 1);
//!bs:end
//!bs:ql.show(var(Vau(1)), [ran(val(0),val(0)), ran(val(1),val(1))], ['Вау &lb;1&rb; - xxx', 'xxx - Вау&lb;1&rb;'], 1 )
AddShowRanges('Vau(1)', [range(0, 0),range(1, 1)], ['Вау (1) - xxx','xxx - Вау(1)'], 1);
//!bs:end
//!bs:ql.icons(var(Vau(1)))
AddIntConstraint('Vau(1)');
//!bs:end
//!bs:end
//!bs:ql.param(var(Ge(10)), var(0))
Ge(10) = 0;AddToVars('Ge(10)');
//!bs:ql.cons(var(Ge(10)), val(0), val(1))
AddConstraint('Ge(10)', 0, 1);
//!bs:end
//!bs:ql.show(var(Ge(10)), [ran(val(0),val(0)), ran(val(1),val(1))], ['Гэ &lb;10&rb; - xxx', 'xxx - Гэ&lb;10&rb;'], 1 )
AddShowRanges('Ge(10)', [range(0, 0),range(1, 1)], ['Гэ (10) - xxx','xxx - Гэ(10)'], 1);
//!bs:end
//!bs:ql.icons(var(Ge(10)))
AddIntConstraint('Ge(10)');
//!bs:end
//!bs:end
//!bs:ql.param(var(Sleva), var(4))
Sleva = 4;AddToVars('Sleva');
//!bs:ql.cons(var(Sleva), val(0), val(4))
AddConstraint('Sleva', 0, 4);
//!bs:end
//!bs:ql.show(var(Sleva), [ran(val(0),val(4))], ['Положение Лодки:'], 1 )
AddShowRanges('Sleva', [range(0, 4)], ['Положение Лодки:'], 1);
//!bs:end
//!bs:ql.icons(var(Sleva))
AddIntConstraint('Sleva');
//!bs:end
//!bs:end
//!bs:ql.param(var(Lodka), var(0))
Lodka = 0;AddToVars('Lodka');
//!bs:ql.cons(var(Lodka), val(0), val(1))
AddConstraint('Lodka', 0, 1);
//!bs:end
//!bs:ql.show(var(Lodka), [ran(val(0),val(0)), ran(val(1),val(1))], ['Лодка - xxx', 'xxx - Лодка'], 1 )
AddShowRanges('Lodka', [range(0, 0),range(1, 1)], ['Лодка - xxx','xxx - Лодка'], 1);
//!bs:end
//!bs:ql.icons(var(Lodka))
AddIntConstraint('Lodka');
//!bs:end
//!bs:end
//!bs:ql.param(var(Ranger), val('<Ranger>'))
Ranger = '<Ranger>';AddToVars('Ranger');
//!bs:end
//!bs:ql.param(var(FromStar), val('<FromStar>'))
FromStar = '<FromStar>';AddToVars('FromStar');
//!bs:end
//!bs:ql.param(var(FromPlanet), val('<FromPlanet>'))
FromPlanet = '<FromPlanet>';AddToVars('FromPlanet');
//!bs:end
//!bs:ql.param(var(ToPlanet), val('<ToPlanet>'))
ToPlanet = '<ToPlanet>';AddToVars('ToPlanet');
//!bs:end
//!bs:ql.param(var(ToStar), val('<ToStar>'))
ToStar = '<ToStar>';AddToVars('ToStar');
//!bs:end
