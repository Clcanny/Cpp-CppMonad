imSquare x | abs x >= 0x8000 = Nothing
           | otherwise       = Just (x * x)

testMaybe =
    return 0x4000 >>= \a ->
    imSquare a    >>= \b ->
    let c = b `div` a in
      return 0.5  >>= \d ->
      imSquare c

cartesianProduct xs ys =
    xs            >>= \x ->
    ys            >>= \y ->
    return (x, y)

testList = cartesianProduct xs ys
  where xs = [1..5]
        ys = map sq xs
        sq x = x * x

main = print testMaybe >> print testList
