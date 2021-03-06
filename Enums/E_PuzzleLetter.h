// Copyright 2020 Vacuda

#pragma once

#include "E_PuzzleLetter.generated.h"

UENUM()
enum E_PuzzleLetter
{
    pNONE           UMETA(DisplayName = "pNONE"),
    pJUNCTION       UMETA(DisplayName = "pJUNCTION"),

    p001            UMETA(DisplayName = "p001"),
    p002            UMETA(DisplayName = "p002"),
    p003            UMETA(DisplayName = "p003"),
    p004            UMETA(DisplayName = "p004"),
    p005            UMETA(DisplayName = "p005"),
    p006            UMETA(DisplayName = "p006"),
    p007            UMETA(DisplayName = "p007"),
    p008            UMETA(DisplayName = "p008"),
    p009            UMETA(DisplayName = "p009"),
    p010            UMETA(DisplayName = "p010"),

    p011            UMETA(DisplayName = "p011"),
    p012            UMETA(DisplayName = "p012"),
    p013            UMETA(DisplayName = "p013"),
    p014            UMETA(DisplayName = "p014"),
    p015            UMETA(DisplayName = "p015"),
    p016            UMETA(DisplayName = "p016"),
    p017            UMETA(DisplayName = "p017"),
    p018            UMETA(DisplayName = "p018"),
    p019            UMETA(DisplayName = "p019"),
    p020            UMETA(DisplayName = "p020"),

    p021            UMETA(DisplayName = "p021"),
    p022            UMETA(DisplayName = "p022"),
    p023            UMETA(DisplayName = "p023"),
    p024            UMETA(DisplayName = "p024"),
    p025            UMETA(DisplayName = "p025"),
    p026            UMETA(DisplayName = "p026"),
    p027            UMETA(DisplayName = "p027"),
    p028            UMETA(DisplayName = "p028"),
    p029            UMETA(DisplayName = "p029"),
    p030            UMETA(DisplayName = "p030"),

    p031            UMETA(DisplayName = "p031"),
    p032            UMETA(DisplayName = "p032"),
    p033            UMETA(DisplayName = "p033"),
    p034            UMETA(DisplayName = "p034"),
    p035            UMETA(DisplayName = "p035"),
    p036            UMETA(DisplayName = "p036"),
    p037            UMETA(DisplayName = "p037"),
    p038            UMETA(DisplayName = "p038"),
    p039            UMETA(DisplayName = "p039"),
    p040            UMETA(DisplayName = "p040"),

    p041            UMETA(DisplayName = "p041"),
    p042            UMETA(DisplayName = "p042"),
    p043            UMETA(DisplayName = "p043"),
    p044            UMETA(DisplayName = "p044"),
    p045            UMETA(DisplayName = "p045"),
    p046            UMETA(DisplayName = "p046"),
    p047            UMETA(DisplayName = "p047"),
    p048            UMETA(DisplayName = "p048"),
    p049            UMETA(DisplayName = "p049"),
    p050            UMETA(DisplayName = "p050"),

    p051            UMETA(DisplayName = "p051"),
    p052            UMETA(DisplayName = "p052"),
    p053            UMETA(DisplayName = "p053"),
    p054            UMETA(DisplayName = "p054"),
    p055            UMETA(DisplayName = "p055"),
    p056            UMETA(DisplayName = "p056"),
    p057            UMETA(DisplayName = "p057"),
    p058            UMETA(DisplayName = "p058"),
    p059            UMETA(DisplayName = "p059"),
    p060            UMETA(DisplayName = "p060"),

    p061            UMETA(DisplayName = "p061"),
    p062            UMETA(DisplayName = "p062"),
    p063            UMETA(DisplayName = "p063"),
    p064            UMETA(DisplayName = "p064"),
    p065            UMETA(DisplayName = "p065"),
    p066            UMETA(DisplayName = "p066"),
    p067            UMETA(DisplayName = "p067"),
    p068            UMETA(DisplayName = "p068"),
    p069            UMETA(DisplayName = "p069"),
    p070            UMETA(DisplayName = "p070"),

    p071            UMETA(DisplayName = "p071"),
    p072            UMETA(DisplayName = "p072"),
    p073            UMETA(DisplayName = "p073"),
    p074            UMETA(DisplayName = "p074"),
    p075            UMETA(DisplayName = "p075"),
    p076            UMETA(DisplayName = "p076"),
    p077            UMETA(DisplayName = "p077"),
    p078            UMETA(DisplayName = "p078"),
    p079            UMETA(DisplayName = "p079"),
    p080            UMETA(DisplayName = "p080"),

    p081            UMETA(DisplayName = "p081"),
    p082            UMETA(DisplayName = "p082"),
    p083            UMETA(DisplayName = "p083"),
    p084            UMETA(DisplayName = "p084"),
    p085            UMETA(DisplayName = "p085"),
    p086            UMETA(DisplayName = "p086"),
    p087            UMETA(DisplayName = "p087"),
    p088            UMETA(DisplayName = "p088"),
    p089            UMETA(DisplayName = "p089"),
    p090            UMETA(DisplayName = "p090"),

    p091            UMETA(DisplayName = "p091"),
    p092            UMETA(DisplayName = "p092"),
    p093            UMETA(DisplayName = "p093"),
    p094            UMETA(DisplayName = "p094"),
    p095            UMETA(DisplayName = "p095"),
    p096            UMETA(DisplayName = "p096"),
    p097            UMETA(DisplayName = "p097"),
    p098            UMETA(DisplayName = "p098"),
    p099            UMETA(DisplayName = "p099"),
    p100            UMETA(DisplayName = "p100"),

    //100s

    p101            UMETA(DisplayName = "p101"),
    p102            UMETA(DisplayName = "p102"),
    p103            UMETA(DisplayName = "p103"),
    p104            UMETA(DisplayName = "p104"),
    p105            UMETA(DisplayName = "p105"),
    p106            UMETA(DisplayName = "p106"),
    p107            UMETA(DisplayName = "p107"),
    p108            UMETA(DisplayName = "p108"),
    p109            UMETA(DisplayName = "p109"),
    p110            UMETA(DisplayName = "p110"),

    p111            UMETA(DisplayName = "p111"),
    p112            UMETA(DisplayName = "p112"),
    p113            UMETA(DisplayName = "p113"),
    p114            UMETA(DisplayName = "p114"),
    p115            UMETA(DisplayName = "p115"),
    p116            UMETA(DisplayName = "p116"),
    p117            UMETA(DisplayName = "p117"),
    p118            UMETA(DisplayName = "p118"),
    p119            UMETA(DisplayName = "p119"),
    p120            UMETA(DisplayName = "p120"),

    p121            UMETA(DisplayName = "p121"),
    p122            UMETA(DisplayName = "p122"),
    p123            UMETA(DisplayName = "p123"),
    p124            UMETA(DisplayName = "p124"),
    p125            UMETA(DisplayName = "p125"),
    p126            UMETA(DisplayName = "p126"),
    p127            UMETA(DisplayName = "p127"),
    p128            UMETA(DisplayName = "p128"),
    p129            UMETA(DisplayName = "p129"),
    p130            UMETA(DisplayName = "p130"),

    p131            UMETA(DisplayName = "p131"),
    p132            UMETA(DisplayName = "p132"),
    p133            UMETA(DisplayName = "p133"),
    p134            UMETA(DisplayName = "p134"),
    p135            UMETA(DisplayName = "p135"),
    p136            UMETA(DisplayName = "p136"),
    p137            UMETA(DisplayName = "p137"),
    p138            UMETA(DisplayName = "p138"),
    p139            UMETA(DisplayName = "p139"),
    p140            UMETA(DisplayName = "p140"),

    p141            UMETA(DisplayName = "p141"),
    p142            UMETA(DisplayName = "p142"),
    p143            UMETA(DisplayName = "p143"),
    p144            UMETA(DisplayName = "p144"),
    p145            UMETA(DisplayName = "p145"),
    p146            UMETA(DisplayName = "p146"),
    p147            UMETA(DisplayName = "p147"),
    p148            UMETA(DisplayName = "p148"),
    p149            UMETA(DisplayName = "p149"),
    p150            UMETA(DisplayName = "p150"),

    p151            UMETA(DisplayName = "p151"),
    p152            UMETA(DisplayName = "p152"),
    p153            UMETA(DisplayName = "p153"),
    p154            UMETA(DisplayName = "p154"),
    p155            UMETA(DisplayName = "p155"),
    p156            UMETA(DisplayName = "p156"),
    p157            UMETA(DisplayName = "p157"),
    p158            UMETA(DisplayName = "p158"),
    p159            UMETA(DisplayName = "p159"),
    p160            UMETA(DisplayName = "p160"),

    p161            UMETA(DisplayName = "p161"),
    p162            UMETA(DisplayName = "p162"),
    p163            UMETA(DisplayName = "p163"),
    p164            UMETA(DisplayName = "p164"),
    p165            UMETA(DisplayName = "p165"),
    p166            UMETA(DisplayName = "p166"),
    p167            UMETA(DisplayName = "p167"),
    p168            UMETA(DisplayName = "p168"),
    p169            UMETA(DisplayName = "p169"),
    p170            UMETA(DisplayName = "p170"),

    p171            UMETA(DisplayName = "p171"),
    p172            UMETA(DisplayName = "p172"),
    p173            UMETA(DisplayName = "p173"),
    p174            UMETA(DisplayName = "p174"),
    p175            UMETA(DisplayName = "p175"),
    p176            UMETA(DisplayName = "p176"),
    p177            UMETA(DisplayName = "p177"),
    p178            UMETA(DisplayName = "p178"),
    p179            UMETA(DisplayName = "p179"),
    p180            UMETA(DisplayName = "p180"),

    p181            UMETA(DisplayName = "p181"),
    p182            UMETA(DisplayName = "p182"),
    p183            UMETA(DisplayName = "p183"),
    p184            UMETA(DisplayName = "p184"),
    p185            UMETA(DisplayName = "p185"),
    p186            UMETA(DisplayName = "p186"),
    p187            UMETA(DisplayName = "p187"),
    p188            UMETA(DisplayName = "p188"),
    p189            UMETA(DisplayName = "p189"),
    p190            UMETA(DisplayName = "p190"),

    p191            UMETA(DisplayName = "p191"),
    p192            UMETA(DisplayName = "p192"),
    p193            UMETA(DisplayName = "p193"),
    p194            UMETA(DisplayName = "p194"),
    p195            UMETA(DisplayName = "p195"),
    p196            UMETA(DisplayName = "p196"),
    p197            UMETA(DisplayName = "p197"),
    p198            UMETA(DisplayName = "p198"),
    p199            UMETA(DisplayName = "p199"),
    p200            UMETA(DisplayName = "p200"),
};