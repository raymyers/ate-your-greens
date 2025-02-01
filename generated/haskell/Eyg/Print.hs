-- File generated by the BNF Converter (bnfc 2.9.6).

{-# LANGUAGE CPP #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE LambdaCase #-}
#if __GLASGOW_HASKELL__ <= 708
{-# LANGUAGE OverlappingInstances #-}
#endif

-- | Pretty-printer for Eyg.

module Eyg.Print where

import Prelude
  ( ($), (.)
  , Bool(..), (==), (<)
  , Int, Integer, Double, (+), (-), (*)
  , String, (++)
  , ShowS, showChar, showString
  , all, elem, foldr, id, map, null, replicate, shows, span
  )
import Data.Char ( Char, isSpace )
import qualified Eyg.Abs

-- | The top-level printing method.

printTree :: Print a => a -> String
printTree = render . prt 0

type Doc = [ShowS] -> [ShowS]

doc :: ShowS -> Doc
doc = (:)

render :: Doc -> String
render d = rend 0 False (map ($ "") $ d []) ""
  where
  rend
    :: Int        -- ^ Indentation level.
    -> Bool       -- ^ Pending indentation to be output before next character?
    -> [String]
    -> ShowS
  rend i p = \case
      "["      :ts -> char '[' . rend i False ts
      "("      :ts -> char '(' . rend i False ts
      "{"      :ts -> onNewLine i     p . showChar   '{'  . new (i+1) ts
      "}" : ";":ts -> onNewLine (i-1) p . showString "};" . new (i-1) ts
      "}"      :ts -> onNewLine (i-1) p . showChar   '}'  . new (i-1) ts
      [";"]        -> char ';'
      ";"      :ts -> char ';' . new i ts
      t  : ts@(s:_) | closingOrPunctuation s
                   -> pending . showString t . rend i False ts
      t        :ts -> pending . space t      . rend i False ts
      []           -> id
    where
    -- Output character after pending indentation.
    char :: Char -> ShowS
    char c = pending . showChar c

    -- Output pending indentation.
    pending :: ShowS
    pending = if p then indent i else id

  -- Indentation (spaces) for given indentation level.
  indent :: Int -> ShowS
  indent i = replicateS (2*i) (showChar ' ')

  -- Continue rendering in new line with new indentation.
  new :: Int -> [String] -> ShowS
  new j ts = showChar '\n' . rend j True ts

  -- Make sure we are on a fresh line.
  onNewLine :: Int -> Bool -> ShowS
  onNewLine i p = (if p then id else showChar '\n') . indent i

  -- Separate given string from following text by a space (if needed).
  space :: String -> ShowS
  space t s =
    case (all isSpace t, null spc, null rest) of
      (True , _   , True ) -> []             -- remove trailing space
      (False, _   , True ) -> t              -- remove trailing space
      (False, True, False) -> t ++ ' ' : s   -- add space if none
      _                    -> t ++ s
    where
      (spc, rest) = span isSpace s

  closingOrPunctuation :: String -> Bool
  closingOrPunctuation [c] = c `elem` closerOrPunct
  closingOrPunctuation _   = False

  closerOrPunct :: String
  closerOrPunct = ")],;"

parenth :: Doc -> Doc
parenth ss = doc (showChar '(') . ss . doc (showChar ')')

concatS :: [ShowS] -> ShowS
concatS = foldr (.) id

concatD :: [Doc] -> Doc
concatD = foldr (.) id

replicateS :: Int -> ShowS -> ShowS
replicateS n f = concatS (replicate n f)

-- | The printer class does the job.

class Print a where
  prt :: Int -> a -> Doc

instance {-# OVERLAPPABLE #-} Print a => Print [a] where
  prt i = concatD . map (prt i)

instance Print Char where
  prt _ c = doc (showChar '\'' . mkEsc '\'' c . showChar '\'')

instance Print String where
  prt _ = printString

printString :: String -> Doc
printString s = doc (showChar '"' . concatS (map (mkEsc '"') s) . showChar '"')

mkEsc :: Char -> Char -> ShowS
mkEsc q = \case
  s | s == q -> showChar '\\' . showChar s
  '\\' -> showString "\\\\"
  '\n' -> showString "\\n"
  '\t' -> showString "\\t"
  s -> showChar s

prPrec :: Int -> Int -> Doc -> Doc
prPrec i j = if j < i then parenth else id

instance Print Integer where
  prt _ x = doc (shows x)

instance Print Double where
  prt _ x = doc (shows x)

instance Print Eyg.Abs.NamedReference where
  prt _ (Eyg.Abs.NamedReference i) = doc $ showString i
instance Print Eyg.Abs.Tag where
  prt _ (Eyg.Abs.Tag i) = doc $ showString i
instance Print Eyg.Abs.Id where
  prt _ (Eyg.Abs.Id i) = doc $ showString i
instance Print Eyg.Abs.Program where
  prt i = \case
    Eyg.Abs.PExps exp -> prPrec i 0 (concatD [prt 0 exp])

instance Print Eyg.Abs.Exp where
  prt i = \case
    Eyg.Abs.ELet matchpattern exp1 exp2 -> prPrec i 1 (concatD [doc (showString "let"), prt 0 matchpattern, doc (showString "="), prt 2 exp1, doc (showString ";"), prt 0 exp2])
    Eyg.Abs.EList listitems -> prPrec i 2 (concatD [doc (showString "["), prt 0 listitems, doc (showString "]")])
    Eyg.Abs.ERecord recordfields -> prPrec i 2 (concatD [doc (showString "{"), prt 0 recordfields, doc (showString "}")])
    Eyg.Abs.ETagged tag exp -> prPrec i 2 (concatD [prt 0 tag, prt 0 exp])
    Eyg.Abs.ELambda params exp -> prPrec i 2 (concatD [doc (showString "|"), prt 0 params, doc (showString "|"), doc (showString "{"), prt 0 exp, doc (showString "}")])
    Eyg.Abs.EPerform exp -> prPrec i 2 (concatD [doc (showString "perform"), prt 2 exp])
    Eyg.Abs.EHandle tag exp1 exp2 -> prPrec i 2 (concatD [doc (showString "handle"), prt 0 tag, doc (showString "("), prt 2 exp1, doc (showString ","), prt 2 exp2, doc (showString ")")])
    Eyg.Abs.EMatch exp matchitems -> prPrec i 2 (concatD [doc (showString "match"), prt 2 exp, doc (showString "{"), doc (showString "case"), prt 0 matchitems, doc (showString "}")])
    Eyg.Abs.EApply exp exps -> prPrec i 3 (concatD [prt 3 exp, doc (showString "("), prt 2 exps, doc (showString ")")])
    Eyg.Abs.ESelect exp id_ -> prPrec i 3 (concatD [prt 3 exp, doc (showString "."), prt 0 id_])
    Eyg.Abs.EVar id_ -> prPrec i 4 (concatD [prt 0 id_])
    Eyg.Abs.EInt n -> prPrec i 4 (concatD [prt 0 n])
    Eyg.Abs.ENegInt n -> prPrec i 4 (concatD [doc (showString "-"), prt 0 n])
    Eyg.Abs.EString str -> prPrec i 4 (concatD [printString str])
    Eyg.Abs.ENamedReference namedreference -> prPrec i 4 (concatD [prt 0 namedreference])

instance Print [Eyg.Abs.ListItem] where
  prt _ [] = concatD []
  prt _ [x] = concatD [prt 0 x]
  prt _ (x:xs) = concatD [prt 0 x, doc (showString ","), prt 0 xs]

instance Print [Eyg.Abs.RecordField] where
  prt _ [] = concatD []
  prt _ [x] = concatD [prt 0 x]
  prt _ (x:xs) = concatD [prt 0 x, doc (showString ","), prt 0 xs]

instance Print [Eyg.Abs.MatchItem] where
  prt _ [] = concatD []
  prt _ [x] = concatD [prt 0 x]
  prt _ (x:xs) = concatD [prt 0 x, doc (showString "case"), prt 0 xs]

instance Print [Eyg.Abs.Exp] where
  prt _ [] = concatD []
  prt _ [x] = concatD [prt 2 x]
  prt _ (x:xs) = concatD [prt 2 x, doc (showString ","), prt 2 xs]

instance Print [Eyg.Abs.Param] where
  prt _ [] = concatD []
  prt _ [x] = concatD [prt 0 x]
  prt _ (x:xs) = concatD [prt 0 x, doc (showString ","), prt 0 xs]

instance Print Eyg.Abs.MatchItem where
  prt i = \case
    Eyg.Abs.MatchItem0 matchpattern exp -> prPrec i 0 (concatD [prt 0 matchpattern, doc (showString "->"), prt 0 exp])

instance Print Eyg.Abs.MatchPattern where
  prt i = \case
    Eyg.Abs.MPTagged tag matchpattern -> prPrec i 0 (concatD [prt 0 tag, prt 0 matchpattern])
    Eyg.Abs.MPRecord recordfields -> prPrec i 0 (concatD [doc (showString "{"), prt 0 recordfields, doc (showString "}")])
    Eyg.Abs.MPId id_ -> prPrec i 0 (concatD [prt 0 id_])

instance Print Eyg.Abs.RecordField where
  prt i = \case
    Eyg.Abs.RFKeyVal id_ exp -> prPrec i 0 (concatD [prt 0 id_, doc (showString ":"), prt 0 exp])
    Eyg.Abs.RFSpread exp -> prPrec i 0 (concatD [doc (showString ".."), prt 0 exp])

instance Print Eyg.Abs.Param where
  prt i = \case
    Eyg.Abs.PId id_ -> prPrec i 0 (concatD [prt 0 id_])

instance Print Eyg.Abs.ListItem where
  prt i = \case
    Eyg.Abs.LIExpr exp -> prPrec i 0 (concatD [prt 0 exp])
    Eyg.Abs.LISpread exp -> prPrec i 0 (concatD [doc (showString ".."), prt 0 exp])
